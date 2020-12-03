#pragma once

#include "Physics2dStandard.hpp"

namespace Physics2d
{

class RigidBody2d;
class ConstraintVelocities2d;
class ConstraintMass2d;

//-------------------------------------------------------------------Constraint
class ConstraintUtilities
{
public:
  static void Load(ConstraintVelocities2d& velocities, const RigidBody2d* body0, const RigidBody2d* body1);
  static void Store(const ConstraintVelocities2d& velocities, RigidBody2d* body0, RigidBody2d* body1);

  static void Load(ConstraintMass2d& masses, const RigidBody2d* body0, const RigidBody2d* body1);
};

}//namespace Physics2d
