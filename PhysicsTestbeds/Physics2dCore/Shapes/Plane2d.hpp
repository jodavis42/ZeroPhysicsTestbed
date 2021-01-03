#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Plane2d
class Plane2d
{
public:
  Plane2d();
  Plane2d(const Vector3& data);

  static Plane2d From2Points(const Vector2& p0, const Vector2& p1);
  static Plane2d FromPointAndNormal(const Vector2& point, const Vector2& normal);

  Vector2 GetNormal() const;
  float GetDistance() const;
  Vector3 GetData() const;

private:
  Vector3 mData = Vector3::cZero;
};

}//namespace Physics2d
