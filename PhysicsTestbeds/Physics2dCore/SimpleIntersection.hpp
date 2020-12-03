#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

class Aabb2d;
class Box2d;
class Circle2d;
class Manifold2d;

//-------------------------------------------------------------------SimpleIntersection
class SimpleIntersection
{
public:
  static bool PointAabb(const Vector2& point, const Aabb2d& aabb);
  static bool AabbCircle(const Aabb2d& aabb0, const Circle2d& circle1, Manifold2d& manifold);
  static bool BoxBox(const Box2d& box0, const Box2d& box1, Manifold2d& manifold);
  static bool BoxCircle(const Box2d& box0, const Circle2d& circle1, Manifold2d& manifold);
  static bool CircleCircle(const Circle2d& circle0, const Circle2d& circle1, Manifold2d& manifold);

  static bool TestIntersection(const Vector2& point, const Aabb2d& aabb);
  static bool TestIntersection(const Aabb2d& aabb0, const Circle2d& circle1, Manifold2d& manifold);
  static bool TestIntersection(const Box2d& box0, const Box2d& box1, Manifold2d& manifold);
  static bool TestIntersection(const Box2d& box0, const Circle2d& circle1, Manifold2d& manifold);
  static bool TestIntersection(const Circle2d& circle0, const Circle2d& circle1, Manifold2d& manifold);
};

}//namespace Physics2d
