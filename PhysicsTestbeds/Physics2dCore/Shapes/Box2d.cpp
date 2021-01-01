#include "Precompiled.hpp"

#include "Shapes/Box2d.hpp"

namespace Physics2d
{

Vector2 Box2d::Search(const Vector2& direction) const
{
  Vector2 localDirection = Matrix2::MultiplyTransposed(mRotation, direction);
  Vector2 result;
  result.x = Math::Sign(localDirection.x) * mHalfExtents.x;
  result.y = Math::Sign(localDirection.y) * mHalfExtents.y;
  result = Math::Multiply(mRotation, result);

  return result + mCenter;
}

}//namespace Physics2d
