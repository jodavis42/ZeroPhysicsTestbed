#include "Precompiled.hpp"

#include "Shapes/Aabb2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Aabb2d
Aabb2d Aabb2d::FromMinMax(const Vector2& min, const Vector2& max)
{
  Aabb2d result;
  result.mMin = min;
  result.mMax = max;
  return result;
}

Aabb2d Aabb2d::FromCenterAndHalfExtents(const Vector2& center, const Vector2& halfExtents)
{
  Vector2 min = center - halfExtents;
  Vector2 max = center + halfExtents;
  return Aabb2d::FromMinMax(min, max);
}

Vector2 Aabb2d::GetCenter() const
{
  return (mMax + mMin) * 0.5f;
}

Vector2 Aabb2d::GetHalfExtents() const
{
  return GetExtents() * 0.5f;
}

Vector2 Aabb2d::GetExtents() const
{
  return (mMax - mMin);
}

Aabb2d Aabb2d::Translate(const Vector2& translation) const
{
  return Aabb2d::FromMinMax(mMin + translation, mMax + translation);
}

Aabb2d Aabb2d::Transform(const Matrix3& transform) const
{
  Matrix3 absTransform;
  for(size_t y = 0; y < 3; ++y)
  {
    for(size_t x = 0; x < 3; ++x)
      absTransform[y][x] = Math::Abs(transform[y][x]);
  }

  Vector2 center = GetCenter();
  Vector2 halfExtents = GetHalfExtents();
  center = Math::TransformPoint(transform, center);
  halfExtents = Math::TransformNormal(absTransform, halfExtents);

  return Aabb2d::FromCenterAndHalfExtents(center, halfExtents);
}

}//namespace Physics2d
