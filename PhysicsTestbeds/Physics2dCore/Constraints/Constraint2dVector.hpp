#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Constraint2dVector
class Constraint2dVector
{
public:
  Constraint2dVector() {}
  Constraint2dVector(const Vector2& linear0, float angular0, const Vector2& linear1, float angular1);

  void operator*(float value);
  void operator+=(const Constraint2dVector& rhs);
  void operator-=(const Constraint2dVector& rhs);
  Constraint2dVector operator+(const Constraint2dVector& rhs);
  Constraint2dVector operator-(const Constraint2dVector& rhs);

  static float Dot(const Constraint2dVector& lhs, const Constraint2dVector& rhs);

  Vector2 mLinear0 = Vector2::cZero;
  float mAngular0 = 0.0f;
  Vector2 mLinear1 = Vector2::cZero;
  float mAngular1 = 0.0f;
};

}//namespace Physics2d
