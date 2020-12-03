#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ConstraintMass2d
class ConstraintMass2d
{
public:
  ConstraintMass2d() {}
  ConstraintMass2d(float invMass0, float invInertia0, float invMass1, float invInertia1)
    : mInvMass0(invMass0), mInvInertia0(invInertia0), mInvMass1(invMass1), mInvInertia1(invInertia1)
  {

  }

  float mInvMass0 = 1.0f;
  float mInvInertia0 = 1.0f;
  float mInvMass1 = 1.0f;
  float mInvInertia1 = 1.0f;
};

}//namespace Physics2d
