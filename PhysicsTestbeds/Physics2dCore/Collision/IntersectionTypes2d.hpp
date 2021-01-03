#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

class Mesh2d;
class Manifold2d;

//-------------------------------------------------------------------IntersectionType
struct IntersectionType
{
  enum Type { Coplanar = 0, Outside, Inside, Overlaps };
  static const char* Names[];

  IntersectionType();
  explicit IntersectionType(Type type);

  operator bool() const;

  Type mType = Coplanar;
};

//-------------------------------------------------------------------RayIntersectionType
struct RayIntersectionType
{
  enum Type { None = -1, StartsInside, Intersection };
  static const char* Names[];

  RayIntersectionType();
  explicit RayIntersectionType(Type type);

  operator bool() const;

  Type mType = None;
};

}//namespace Physics2d
