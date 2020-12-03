#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Box2d
class Box2d
{
public:
  
  Vector2 mCenter = Vector2::cZero;
  Vector2 mHalfExtents = Vector2(0.5f);
  Matrix2 mRotation = Matrix2::cIdentity;
};

}//namespace Physics2d
