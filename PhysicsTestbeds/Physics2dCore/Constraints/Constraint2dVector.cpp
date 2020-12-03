#include "Precompiled.hpp"

#include "Physics2dCore/Constraints/Constraint2dVector.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Constraint2dVector

Constraint2dVector::Constraint2dVector(const Vector2& linear0, float angular0, const Vector2& linear1, float angular1)
  : mLinear0(linear0), mAngular0(angular0), mLinear1(linear1), mAngular1(angular1)
{

}

void Constraint2dVector::operator*(float value)
{
  mLinear0 *= value;
  mAngular0 *= value;
  mLinear1 *= value;
  mAngular1 *= value;
}

void Constraint2dVector::operator+=(const Constraint2dVector& rhs)
{
  mLinear0 += rhs.mLinear0;
  mAngular0 += rhs.mAngular0;
  mLinear1 += rhs.mLinear1;
  mAngular1 += rhs.mAngular1;
}

void Constraint2dVector::operator-=(const Constraint2dVector& rhs)
{
  mLinear0 -= rhs.mLinear0;
  mAngular0 -= rhs.mAngular0;
  mLinear1 -= rhs.mLinear1;
  mAngular1 -= rhs.mAngular1;
}

Constraint2dVector Constraint2dVector::operator+(const Constraint2dVector& rhs)
{
  Constraint2dVector result = *this;
  result += rhs;
  return result;
}

Constraint2dVector Constraint2dVector::operator-(const Constraint2dVector& rhs)
{
  Constraint2dVector result = *this;
  result -= rhs;
  return result;
}

float Constraint2dVector::Dot(const Constraint2dVector& lhs, const Constraint2dVector& rhs)
{
  float linear0 = Math::Dot(lhs.mLinear0, rhs.mLinear0);
  float linear1 = Math::Dot(lhs.mLinear1, rhs.mLinear1);
  float angular0 = lhs.mAngular0 * rhs.mAngular0;
  float angular1 = lhs.mAngular1 * rhs.mAngular1;
  return linear0 + linear1 + angular0 + angular1;
}

}//namespace Physics2d
