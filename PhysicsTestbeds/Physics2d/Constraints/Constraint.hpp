#pragma once

#include "Physics2dStandard.hpp"

namespace Physics2d
{

class RigidBody2d;

//-------------------------------------------------------------------Constraint
class Constraint : public Zero::Component
{
public:
  ZilchDeclareType(Constraint, TypeCopyMode::ReferenceType);

  void Serialize(Zero::Serializer& stream) override;

  virtual void Solve(float dt) {}

  bool mActive = true;
  Zero::Link<Constraint> mSolverLink;
};

}//namespace Physics2d
