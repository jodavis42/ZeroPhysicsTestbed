#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ManifoldPoint2d
class ManifoldPoint2d
{
public:
  void Flip();

  Vector2 mPoint0 = Vector2::cZero;
  Vector2 mPoint1 = Vector2::cZero;
  Vector2 mNormal = Vector2::cZero;
  float mPenetrationDistance = 0.0f;
};

//-------------------------------------------------------------------Manifold2d
class Manifold2d
{
public:
  void Flip();

  ManifoldPoint2d mPoints[2]{};
  byte mPointCount = 0;
};

}//namespace Physics2d
