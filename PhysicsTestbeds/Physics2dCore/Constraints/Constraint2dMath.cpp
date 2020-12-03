#include "Precompiled.hpp"

#include "Physics2dCore/Constraints/Constraint2dMath.hpp"

#include "ConstraintMass2d.hpp"
#include "Jacobian2d.hpp"
#include "ConstraintVelocities2d.hpp"
#include "Constraint2dMolecule.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ConstraintMath
float ConstraintMath::Dot(const Jacobian2d& jacobian, const ConstraintVelocities2d& velocities)
{
  return Constraint2dVector::Dot(jacobian, velocities);
}

float ConstraintMath::Multiply(const Jacobian2d& jacobian, const ConstraintMass2d& masses)
{
  float linear0 = Math::Dot(jacobian.mLinear0, jacobian.mLinear0) * masses.mInvMass0;
  float linear1 = Math::Dot(jacobian.mLinear1, jacobian.mLinear1) * masses.mInvMass1;
  float angular0 = (jacobian.mAngular0 * jacobian.mAngular0) * masses.mInvInertia0;
  float angular1 = (jacobian.mAngular1 * jacobian.mAngular1) * masses.mInvInertia1;
  return linear0 + linear1 + angular0 + angular1;
}

void ConstraintMath::Apply(ConstraintVelocities2d& velocities, float impulse, const Jacobian2d& jacobian, const ConstraintMass2d& masses)
{
  velocities.mLinear0 += impulse * jacobian.mLinear0 * masses.mInvMass0;
  velocities.mLinear1 += impulse * jacobian.mLinear1 * masses.mInvMass1;
  velocities.mAngular0 += impulse * jacobian.mAngular0 * masses.mInvInertia0;
  velocities.mAngular1 += impulse * jacobian.mAngular1 * masses.mInvInertia1;
}

float ConstraintMath::ComputeLambda(const ConstraintVelocities2d& velocities, Constraint2dMolecule& molecule)
{
  const Jacobian2d& jacobian = molecule.mJacobian;
  float jv = Constraint2dVector::Dot(jacobian, velocities);
  float impulse = -(jv + molecule.mBias) / molecule.mEffectiveMass;

  float oldImpulse = molecule.mTotalImpulse;
  float clampedImpulse = Math::Clamp(oldImpulse + impulse, molecule.mMinImpulse, molecule.mMaxImpulse);
  float deltaImpulse = clampedImpulse - oldImpulse;
  molecule.mTotalImpulse = clampedImpulse;

  return deltaImpulse;
}

}//namespace Physics2d
