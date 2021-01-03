#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------IntersectionInterval2d
struct IntersectionInterval2d
{
  IntersectionInterval2d();
  IntersectionInterval2d(float t0, float t1);

  float GetT() const;
  bool IsValid() const;

  float mT0 = 1.0f;
  float mT1 = -1.0f;
};

}//namespace Physics2d
