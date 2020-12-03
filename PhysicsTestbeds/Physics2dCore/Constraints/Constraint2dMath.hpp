#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

class Jacobian2d;
class ConstraintVelocities2d;
class ConstraintMass2d;
class Constraint2dMolecule;

//-------------------------------------------------------------------ConstraintMath
class ConstraintMath
{
public:
  static float Dot(const Jacobian2d& jacobian, const ConstraintVelocities2d& velocities);
  static float Multiply(const Jacobian2d& jacobian, const ConstraintMass2d& masses);
  static void Apply(ConstraintVelocities2d& velocities, float impulse, const Jacobian2d& jacobian, const ConstraintMass2d& masses);

  static float ComputeLambda(const ConstraintVelocities2d& velocities, Constraint2dMolecule& molecule);
  //static float Solve(const ConstraintVelocities2d& velocities, const Jacobian2d& jacobian, const ConstraintMass2d& masses, float bias)
  //{
  //  float jv = Constraint2dVector::Dot(jacobian, velocities);
  //  float denom = ConstraintMath::Multiply(jacobian, mMasses);
  //  float impulse = -(jv + bias) / denom;
  //  return impulse;
  //}
};

}//namespace Physics2d
