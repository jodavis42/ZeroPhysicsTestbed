#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Aabb2d
class Aabb2d
{
public:
  static Aabb2d FromMinMax(const Vector2& min, const Vector2& max);
  static Aabb2d FromCenterAndHalfExtents(const Vector2& center, const Vector2& halfExtents);

  Vector2 GetCenter() const;
  Vector2 GetHalfExtents() const;
  Vector2 GetExtents() const;

  Aabb2d Translate(const Vector2& translation) const;
  Aabb2d Transform(const Matrix3& transform) const;

  Vector2 mMin = Vector2::cZero;
  Vector2 mMax = Vector2::cZero;
};

}//namespace Physics2d
