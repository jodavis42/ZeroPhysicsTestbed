#include "Precompiled.hpp"

#include "PrimitiveGeometry2d.hpp"

namespace Physics2d
{

IntersectionType::Type PrimitiveGeometry2d::PointPlane(const Vector2& point, const Vector3& planeData, float epsilon)
{
  float dist = Math::Dot(planeData, Vector3(point.x, point.y, -1.0f));
  if(dist > epsilon)
    return IntersectionType::Inside;
  else if(dist < -epsilon)
    return IntersectionType::Outside;
  return IntersectionType::Coplanar;
}

bool PrimitiveGeometry2d::PointAabb(const Vector2& point, const Vector2& aabbMin, const Vector2& aabbMax)
{
  return !(point.x < aabbMin.x || aabbMax.x < point.x ||
    point.y < aabbMin.y || aabbMax.y < point.y);
}

bool PrimitiveGeometry2d::PointCircle(const Vector2& point, const Vector2& circleCenter, float circleRadius)
{
  float distSq = Math::DistanceSq(point, circleCenter);
  return distSq <= Math::Sq(circleRadius);
}

bool PrimitiveGeometry2d::RayPlane(const Vector2& rayStart, const Vector2& rayDir, const Vector3& planeData, float& t, float parallelCheckEpsilon)
{
  Vector2 planeNormal = Vector2(planeData.x, planeData.y);
  float planeDist = planeData.z;

  float denom = Math::Dot(planeNormal, rayDir);
  if(Math::Abs(denom) <= parallelCheckEpsilon)
    return false;

  float numer = planeDist - Math::Dot(planeNormal, rayStart);
  t = numer / denom;
  return t >= 0.0f;
}

RayIntersectionType PrimitiveGeometry2d::RayAabb(const Vector2& rayStart, const Vector2& rayDir, const Vector2& aabbMin, const Vector2& aabbMax, IntersectionInterval2d& interval, float parallelCheckEpsilon)
{
  float tMin = -Math::PositiveMax();
  float tMax = Math::PositiveMax();
  for(size_t axis = 0; axis < 2; ++axis)
  {
    float denom = rayDir[axis];
    if(Math::Abs(denom) < parallelCheckEpsilon)
    {
      if(rayStart[axis] < aabbMin[axis] || aabbMax[axis] < rayStart[axis])
        return RayIntersectionType(RayIntersectionType::None);
    }

    float t0 = (aabbMin[axis] - rayStart[axis]) / denom;
    float t1 = (aabbMax[axis] - rayStart[axis]) / denom;
    if(denom < 0)
      Math::Swap(t0, t1);

    tMin = Math::Max(t0, tMin);
    tMax = Math::Min(t1, tMax);
    if(tMax < tMin)
      return RayIntersectionType(RayIntersectionType::None);
  }
  interval.mT0 = tMin;
  interval.mT1 = tMax;
  
  if(tMax < 0)
    return RayIntersectionType(RayIntersectionType::None);
  if(tMin < 0)
    return RayIntersectionType(RayIntersectionType::StartsInside);
  return RayIntersectionType(RayIntersectionType::Intersection);
}

RayIntersectionType PrimitiveGeometry2d::RayAabb(const Vector2& rayStart, const Vector2& rayDir, const Vector2& aabbMin, const Vector2& aabbMax, float& t, float parallelCheckEpsilon)
{
  IntersectionInterval2d interval;
  RayIntersectionType result = RayAabb(rayStart, rayDir, aabbMin, aabbMax, interval, parallelCheckEpsilon);
  if(result)
    t = interval.GetT();
  return result;
}

RayIntersectionType PrimitiveGeometry2d::RayCircle(const Vector2& rayStart, const Vector2& rayDir, const Vector2& circleCenter, float circleRadius, IntersectionInterval2d& interval)
{
  Vector2 m = circleCenter - rayStart;
  float a = Math::Dot(rayDir, rayDir);
  float b = -2 * Math::Dot(m, rayDir);
  float c = Math::Dot(m, m) - circleRadius * circleRadius;

  float denom = 2 * a;
  if(denom < 0)
    return RayIntersectionType(RayIntersectionType::None);

  float disc = b * b - 4 * a * c;
  if(disc < 0)
    return RayIntersectionType(RayIntersectionType::None);
  interval.mT0 = (-b - Math::Sqrt(disc)) / denom;
  interval.mT1 = (-b + Math::Sqrt(disc)) / denom;
  if(interval.mT1 < 0)
    return RayIntersectionType(RayIntersectionType::None);
  if(interval.mT0 < 0)
    return RayIntersectionType(RayIntersectionType::StartsInside);
  return RayIntersectionType(RayIntersectionType::Intersection);
}

RayIntersectionType PrimitiveGeometry2d::RayCircle(const Vector2& rayStart, const Vector2& rayDir, const Vector2& circleCenter, float circleRadius, float& t)
{
  IntersectionInterval2d interval;
  RayIntersectionType result = RayCircle(rayStart, rayDir, circleCenter, circleRadius, interval);
  if(result)
    t = interval.GetT();
  return result;
}

bool PrimitiveGeometry2d::AabbAabb(const Vector2& aabb0Min, const Vector2& aabb0Max, const Vector2& aabb1Min, const Vector2& aabb1Max)
{
  for(size_t axis = 0; axis < 2; ++axis)
  {
    if(aabb0Max[axis] < aabb1Min[axis] || aabb1Max[axis] < aabb0Min[axis])
      return false;
  }
  return true;
}

bool PrimitiveGeometry2d::CircleCircle(const Vector2& circle0Center, float circle0Radius, const Vector2& circle1Center, float circle1Radius)
{
  return PointCircle(circle0Center, circle1Center, circle0Radius + circle1Radius);
}

}//namespace Physics2d
