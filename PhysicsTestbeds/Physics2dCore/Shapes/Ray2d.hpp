#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Ray2d
class Ray2d
{
public:
  static Ray2d From2Points(const Vector2& p0, const Vector2& p1);
  static Ray2d FromPointAndDirection(const Vector2& point, const Vector2& direction);

  Vector2 GetStart() const;
  Vector2 GetDirection() const;
  Vector2 GetPoint(float t) const;

private:
  Vector2 mStart;
  Vector2 mDirection;
};

}//namespace Physics2d
