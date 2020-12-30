#pragma once

#include "Physics2d/Physics2dStandard.hpp"

#include "RigidBody2d.hpp"
#include "Components/Colliders/Collider2d.hpp"
#include "Components/Colliders/Collider2dPair.hpp"
#include "CollisionDetection/ContactManifold2d.hpp"
#include "Physics2dCore/SpatialPartitions/NSquaredSpatialPartition.hpp"

namespace Physics2d
{

class RigidBody2d;
class CollisionLibrary;
class Physics2dNodeManager;
class Manifold2d;

//-------------------------------------------------------------------PhysicsSpace
class PhysicsSpace2d : public Zero::Component
{
public:
  ZilchDeclareType(PhysicsSpace2d, TypeCopyMode::ReferenceType);

  using SpatialPartitionDataType = SpatialPartitionData<Collider2d*>;

  PhysicsSpace2d();
  ~PhysicsSpace2d();

  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer) override;
  void OnDestroy(uint flags) override;

  void SystemLogicUpdate(Zero::UpdateEvent* updateEvent);

  void Add(RigidBody2d* body);
  void Remove(RigidBody2d* body);
  void UpdateRigidBodyDynamicState(RigidBody2d* body);
  void Add(Collider2d* collider);
  void Remove(Collider2d* collider);
  
  CollisionLibrary* GetCollisionLibrary() const;
  void ToSpatialPartitionData(Collider2d* collider, SpatialPartitionDataType& data);
  NSquaredSpatialPartition<Collider2d*> mSpatialPartition;

private:

  void Update(float dt);
  void IntegrateVelocities(float dt);
  void IntegratePositions(float dt);
  void BroadPhase(float dt, Array<Collider2dPair>& possiblePairs);
  void NarrowPhase(float dt, const Array<Collider2dPair>& possiblePairs, Array<ContactManifold2d>& manifolds);
  void ResolutionPhase(float dt, Array<ContactManifold2d>& manifolds);
  void PublishTransforms();

  bool ShouldResolveCollisions(const Collider2d* collider0, const Collider2d* collider1);

  Zero::InList<RigidBody2d, &RigidBody2d::mSpaceLink> mRigidBodies;
  Zero::InList<Collider2d, &Collider2d::mSpaceLink> mColliders;
  CollisionLibrary* mCollisionLibrary = nullptr;
  Physics2dNodeManager* mNodeManager = nullptr;
};

}//namespace Physics2d
