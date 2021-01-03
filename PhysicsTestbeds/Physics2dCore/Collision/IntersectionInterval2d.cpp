#include "Precompiled.hpp"

#include "IntersectionInterval2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------IntersectionInterval2d
IntersectionInterval2d::IntersectionInterval2d() {}

IntersectionInterval2d::IntersectionInterval2d(float t0, float t1)
  : mT0(t0)
  , mT1(t1)
{
}

float IntersectionInterval2d::GetT() const
{
  return Math::Max(0.0f, mT0);
}

bool IntersectionInterval2d::IsValid() const
{
  return mT0 <= mT1;
}

}//namespace Physics2d
