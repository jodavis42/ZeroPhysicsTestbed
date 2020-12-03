#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Circle2d
class Circle2d
{
public:
  Circle2d();
  Circle2d(const Vector2& center, float radius);

  Circle2d Transform(const Matrix3& transform) const;

  float mRadius = 1.0f;
  Vector2 mCenter = Vector2::cZero;
};

}//namespace Physics2d
