#pragma once

#include "Physics2dStandard.hpp"

#include "Constraint.hpp"
#include "CollisionDetection/ContactManifold2d.hpp"
#include "Constraints/ConstraintMass2d.hpp"
#include "Constraints/Jacobian2d.hpp"
#include "Constraints/ConstraintVelocities2d.hpp"
#include "Constraints/Constraint2dMolecule.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ContactConstraint
class ContactConstraint : public Constraint
{
public:
  ZilchDeclareType(ContactConstraint, TypeCopyMode::ReferenceType);

  void Setup(const ContactManifold2d& manifold);
  void Solve(float dt) override;
  
private:
  void Solve(ConstraintVelocities2d& velocities, Constraint2dMolecule& molecule);

  RigidBody2d* mBodies[2]{};
  ContactManifold2d mManifold;
  ConstraintMass2d mMasses;
  
  Constraint2dMolecule mNormalConstraints[2]{};
  Constraint2dMolecule mTangentConstraints[2]{};
};

}//namespace Physics2d
