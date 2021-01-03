#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

#include "Collision/IntersectionInterval2d.hpp"
#include "Collision/IntersectionTypes2d.hpp"

namespace Physics2d
{

class Mesh2d;
class Manifold2d;

//-------------------------------------------------------------------PrimitiveGeometry2d
class PrimitiveGeometry2d
{
public:
  static IntersectionType::Type PointPlane(const Vector2& point, const Vector3& planeData, float epsilon);
  static bool PointAabb(const Vector2& point, const Vector2& aabbMin, const Vector2& aabbMax);
  static bool PointCircle(const Vector2& point, const Vector2& circleCenter, float circleRadius);

  static bool RayPlane(const Vector2& rayStart, const Vector2& rayDir, const Vector3& planeData, float& t, float parallelCheckEpsilon = 0.0001f);

  static RayIntersectionType RayAabb(const Vector2& rayStart, const Vector2& rayDir, const Vector2& aabbMin, const Vector2& aabbMax, IntersectionInterval2d& interval, float parallelCheckEpsilon = 0.0001f);
  static RayIntersectionType RayAabb(const Vector2& rayStart, const Vector2& rayDir, const Vector2& aabbMin, const Vector2& aabbMax, float& t, float parallelCheckEpsilon = 0.0001f);

  static RayIntersectionType RayCircle(const Vector2& rayStart, const Vector2& rayDir, const Vector2& circleCenter, float circleRadius, IntersectionInterval2d& interval);
  static RayIntersectionType RayCircle(const Vector2& rayStart, const Vector2& rayDir, const Vector2& circleCenter, float circleRadius, float& t);

  static bool AabbAabb(const Vector2& aabb0Min, const Vector2& aabb0Max, const Vector2& aabb1Min, const Vector2& aabb1Max);

  static bool CircleCircle(const Vector2& circle0Center, float circle0Radius, const Vector2& circle1Center, float circle1Radius);
};

}//namespace Physics2d
