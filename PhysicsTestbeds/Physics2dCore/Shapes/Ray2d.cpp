#include "Precompiled.hpp"

#include "Ray2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Ray2d
Ray2d Ray2d::From2Points(const Vector2& p0, const Vector2& p1)
{
  return FromPointAndDirection(p0, p1 - p0);
}

Ray2d Ray2d::FromPointAndDirection(const Vector2& point, const Vector2& direction)
{
  Ray2d result;
  result.mStart = point;
  result.mDirection = Math::AttemptNormalized(direction);
  return result;
}

Vector2 Ray2d::GetStart() const
{
  return mStart;
}

Vector2 Ray2d::GetDirection() const
{
  return mDirection;
}

Vector2 Ray2d::GetPoint(float t) const
{
  return mStart + mDirection * t;
}

}//namespace Physics2d
