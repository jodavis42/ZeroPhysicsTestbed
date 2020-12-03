#include "Precompiled.hpp"

#include "ContactConstraint.hpp"

#include "Engine/Cog.hpp"
#include "Engine/Space.hpp"

#include "Components/PhysicsSpace2d.hpp"
#include "Constraints/ConstraintUtilities.hpp"
#include "Physics2dCore/Constraints/Constraint2dMath.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ContactConstraint
ZilchDefineType(ContactConstraint, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::FromDataOnly);
}

void ContactConstraint::Setup(const ContactManifold2d& manifold)
{
  mManifold = manifold;
  mBodies[0] = manifold.mPair[0]->GetOwner()->has(RigidBody2d);
  mBodies[1] = manifold.mPair[1]->GetOwner()->has(RigidBody2d);
  ConstraintUtilities::Load(mMasses, mBodies[0], mBodies[1]);

  ConstraintVelocities2d velocities;
  ConstraintUtilities::Load(velocities, mBodies[0], mBodies[1]);
  float restitution = mManifold.mPair.GetRestitution();
  float dynamicFriction = mManifold.mPair.GetDynamicFriction();

  for(size_t i = 0; i < mManifold.mPointCount; ++i)
  {
    const ManifoldPoint2d& point = mManifold.mPoints[i];
    Vector2 normal = point.mNormal;
    Vector2 tangent = Vector2(-normal.y, normal.x);
    Vector2 r0 = point.mPoint0 - mBodies[0]->GetWorldCenterOfMass();
    Vector2 r1 = point.mPoint1 - mBodies[1]->GetWorldCenterOfMass();

    Constraint2dMolecule& normalConstraint = mNormalConstraints[i];
    normalConstraint.mJacobian = Jacobian2d(-normal, -Math::Cross(r0, normal), normal, Math::Cross(r1, normal));
    normalConstraint.mEffectiveMass = ConstraintMath::Multiply(normalConstraint.mJacobian, mMasses);
    normalConstraint.mTotalImpulse = 0.0f;
    normalConstraint.mMinImpulse = 0.0f;
    normalConstraint.mMaxImpulse = Math::PositiveMax();
    float normalJv = Constraint2dVector::Dot(normalConstraint.mJacobian, velocities);
    normalConstraint.mBias = normalJv * restitution;

    Constraint2dMolecule& tangentConstraint = mTangentConstraints[i];
    tangentConstraint.mJacobian = Jacobian2d(-tangent, -Math::Cross(r0, tangent), tangent, Math::Cross(r1, tangent));
    tangentConstraint.mEffectiveMass = ConstraintMath::Multiply(tangentConstraint.mJacobian, mMasses);
    tangentConstraint.mTotalImpulse = 0.0f;
    float tangentLimit = dynamicFriction * 10 / tangentConstraint.mEffectiveMass;
    tangentConstraint.mMinImpulse = -tangentLimit;
    tangentConstraint.mMaxImpulse = tangentLimit;
  }
}

void ContactConstraint::Solve(float dt)
{
  ConstraintVelocities2d velocities;
  ConstraintUtilities::Load(velocities, mBodies[0], mBodies[1]);

  for(size_t i = 0; i < mManifold.mPointCount; ++i)
  {
    Solve(velocities, mNormalConstraints[i]);
    Solve(velocities, mTangentConstraints[i]);
  }
  
  ConstraintUtilities::Store(velocities, mBodies[0], mBodies[1]);
}

void ContactConstraint::Solve(ConstraintVelocities2d& velocities, Constraint2dMolecule& molecule)
{
  float impulse = ConstraintMath::ComputeLambda(velocities, molecule);
  ConstraintMath::Apply(velocities, impulse, molecule.mJacobian, mMasses);
}

}//namespace Physics2d
