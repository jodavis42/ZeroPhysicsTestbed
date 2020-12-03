#include "Precompiled.hpp"

#include "ContactConstraint.hpp"

#include "ConstraintUtilities.hpp"

#include "Constraints/ConstraintMass2d.hpp"
#include "Constraints/Jacobian2d.hpp"
#include "Constraints/ConstraintVelocities2d.hpp"
#include "Constraints/ConstraintMass2d.hpp"
#include "Components/RigidBody2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Constraint
void ConstraintUtilities::Load(ConstraintVelocities2d& velocities, const RigidBody2d* body0, const RigidBody2d* body1)
{
  velocities.mLinear0 = velocities.mLinear1 = Vector2::cZero;
  velocities.mAngular0 = velocities.mAngular1 = 0.0f;
  if(body0 != nullptr)
    body0->GetVelocities(velocities.mLinear0, velocities.mAngular0);
  if(body1 != nullptr)
    body1->GetVelocities(velocities.mLinear1, velocities.mAngular1);
}

void ConstraintUtilities::Store(const ConstraintVelocities2d& velocities, RigidBody2d* body0, RigidBody2d* body1)
{
  if(body0 != nullptr)
    body0->SetVelocities(velocities.mLinear0, velocities.mAngular0);
  if(body1 != nullptr)
    body1->SetVelocities(velocities.mLinear1, velocities.mAngular1);
}

void ConstraintUtilities::Load(ConstraintMass2d& masses, const RigidBody2d* body0, const RigidBody2d* body1)
{
  masses.mInvInertia0 = masses.mInvInertia1 = masses.mInvMass0 = masses.mInvMass1 = 0.0f;
  if(body0 != nullptr)
  {
    masses.mInvMass0 = body0->GetInvMass();
    masses.mInvInertia0 = body0->GetInvInertia();
  }
  if(body1 != nullptr)
  {
    masses.mInvMass1 = body1->GetInvMass();
    masses.mInvInertia1 = body1->GetInvInertia();
  }
}

}//namespace Physics2d
