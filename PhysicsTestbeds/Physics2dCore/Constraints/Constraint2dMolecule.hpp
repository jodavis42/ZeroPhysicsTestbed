#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"
#include "Physics2dCore/Constraints/Jacobian2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Constraint2dMolecule
class Constraint2dMolecule
{
public:
  Jacobian2d mJacobian;
  float mEffectiveMass = 0.0f;
  float mTotalImpulse = 0.0f;
  float mMinImpulse = 0.0f;
  float mMaxImpulse = 0.0f;
  float mBias = 0.0f;
  float mGamma = 0.0f;
};

}//namespace Physics2d
