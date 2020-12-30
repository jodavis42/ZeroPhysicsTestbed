#include "Precompiled.hpp"

#include "Components/PhysicsSpace2d.hpp"
#include "Physics2dCore/Integrators2d.hpp"
#include "CollisionDetection/CollisionLibrary.hpp"
#include "Physics2dCore/Constraints/Constraint2dMath.hpp"
#include "Constraints/ConstraintSolver.hpp"
#include "Constraints/ContactConstraint.hpp"
#include "Utilities/Physics2dNodeManager.hpp"
#include "Utilities/ZeroUtilities.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------PhysicsSpace2d
ZilchDefineType(PhysicsSpace2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Space);
}

PhysicsSpace2d::PhysicsSpace2d()
{
  mCollisionLibrary = new CollisionLibrary();
  mNodeManager = new Physics2dNodeManager();
}

PhysicsSpace2d::~PhysicsSpace2d()
{
  delete mNodeManager;
  delete mCollisionLibrary;
}

void PhysicsSpace2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void PhysicsSpace2d::Initialize(Zero::CogInitializer& initializer)
{
  ConnectThisTo(GetOwner(), Zero::Events::SystemLogicUpdate, SystemLogicUpdate);
}

void PhysicsSpace2d::OnDestroy(uint flags)
{

}

void PhysicsSpace2d::SystemLogicUpdate(Zero::UpdateEvent* updateEvent)
{
  Update(updateEvent->Dt);
}

void PhysicsSpace2d::Add(RigidBody2d* body)
{
  mRigidBodies.PushBack(body);

  Physics2dNode* node = mNodeManager->GetOrCreateNode(body->GetOwner());
  node->SetBody(body);
  node->QueueMassCalculation();
}

void PhysicsSpace2d::Remove(RigidBody2d* body)
{
  mRigidBodies.Erase(body);

  Physics2dNode* node = mNodeManager->GetNode(body->GetOwner());
  node->ClearBody();
}

void PhysicsSpace2d::UpdateRigidBodyDynamicState(RigidBody2d* body)
{
  
}

void PhysicsSpace2d::Add(Collider2d* collider)
{
  mColliders.PushBack(collider);

  Physics2dNode* node = mNodeManager->GetOrCreateNode(collider->GetOwner());
  node->SetCollider(collider);
  node->QueueBroadphaseInsert();
}

void PhysicsSpace2d::Remove(Collider2d* collider)
{
  mColliders.Erase(collider);

  Physics2dNode* node = mNodeManager->GetNode(collider->GetOwner());
  node->QueueBroadphaseRemoval();
  node->ClearCollider();
}

CollisionLibrary* PhysicsSpace2d::GetCollisionLibrary() const
{
  return mCollisionLibrary;
}

void PhysicsSpace2d::ToSpatialPartitionData(Collider2d* collider, SpatialPartitionDataType& data)
{
  collider->UpdateBoundingVolumes();
  data.mUserData = collider;
  data.mAabb = collider->GetWorldAabb();
  data.mCircle = collider->GetWorldCircle();
}

void PhysicsSpace2d::Update(float dt)
{
  mNodeManager->ProcessQueue(this);
  IntegrateVelocities(dt);

  Array<Collider2dPair> possiblePairs;
  BroadPhase(dt, possiblePairs);

  Array<ContactManifold2d> manifolds;
  NarrowPhase(dt, possiblePairs, manifolds);

  ResolutionPhase(dt, manifolds);
  IntegratePositions(dt);
  PublishTransforms();
}

void PhysicsSpace2d::IntegrateVelocities(float dt)
{
  auto bodyRange = mRigidBodies.All();
  for(; !bodyRange.Empty(); bodyRange.PopFront())
  {
    RigidBody2d& body = bodyRange.Front();

    // @JoshD: Hack - remove
    float invMass = body.GetInvMass();
    if(invMass != 0.0f)
      body.mForce += -10 / invMass * Vector2(0, 1);

    EulerIntegrator::IntegrateLinearVelocity(body.mLinearVelocity, body.mForce, body.GetInvMass(), dt);
    EulerIntegrator::IntegrateAngularVelocity(body.mAngularVelocity, body.mTorque, body.GetInvInertia(), dt);
    body.mForce = Vector2::cZero;
  }
}

void PhysicsSpace2d::IntegratePositions(float dt)
{
  auto bodyRange = mRigidBodies.All();
  for(; !bodyRange.Empty(); bodyRange.PopFront())
  {
    RigidBody2d& body = bodyRange.Front();
    EulerIntegrator::IntegratePosition(body.mWorldCenterOfMass, body.mLinearVelocity, dt);
    EulerIntegrator::IntegrateRotation(body.mWorldRotation, body.mAngularVelocity, dt);
    body.GetNode()->QueueBroadphaseUpdate();
  }
}

void PhysicsSpace2d::BroadPhase(float dt, Array<Collider2dPair>& possiblePairs)
{
  for(auto range = mSpatialPartition.SelfQuery(); !range.Empty(); range.PopFront())
  {
    SelfQueryResult<Collider2d*> selfQueryPair = range.Front();
    Collider2dPair pair(selfQueryPair.mUserData0, selfQueryPair.mUserData1);
    possiblePairs.PushBack(pair);
  }
}

void PhysicsSpace2d::NarrowPhase(float dt, const Array<Collider2dPair>& possiblePairs, Array<ContactManifold2d>& manifolds)
{
  for(auto range = possiblePairs.All(); !range.Empty(); range.PopFront())
  {
    Collider2dPair& pair = range.Front();
    mCollisionLibrary->TestPair(pair[0], pair[1], manifolds);
  }
}

void PhysicsSpace2d::ResolutionPhase(float dt, Array<ContactManifold2d>& manifolds)
{
  ConstraintSolver solver;
  for(auto range = manifolds.All(); !range.Empty(); range.PopFront())
  {
    ContactManifold2d& manifold = range.Front();
    if(!ShouldResolveCollisions(manifold.mPair[0], manifold.mPair[1]))
      continue;

    ContactConstraint* contact = new ContactConstraint();
    contact->Setup(manifold);
    solver.Add(contact);
  }

  solver.Solve(dt);

  // @JoshD: Hack - cleanup
  while(!solver.mConstraints.Empty())
  {
    Constraint* constraint = &solver.mConstraints.Front();
      solver.mConstraints.PopFront();
    delete constraint;
  }
}

void PhysicsSpace2d::PublishTransforms()
{
  auto bodyRange = mRigidBodies.All();
  for(; !bodyRange.Empty(); bodyRange.PopFront())
  {
    RigidBody2d& body = bodyRange.Front();
    Zero::Transform* transform = body.GetOwner()->has(Zero::Transform);
    ZeroUtilities::SetWorldTranslation(transform, body.mWorldCenterOfMass);
    ZeroUtilities::SetWorldRotation(transform, body.mWorldRotation);
    transform->UpdateAll(Zero::TransformUpdateFlags::Physics);
  }
}

bool PhysicsSpace2d::ShouldResolveCollisions(const Collider2d* collider0, const Collider2d* collider1)
{
  // If either body is a ghost, then don't resovle
  bool isGhost = collider0->GetIsGhost() || collider1->GetIsGhost();
  return !isGhost;
}

}//namespace Physics2d
