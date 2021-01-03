#include "Precompiled.hpp"

#include "SimpleIntersection.hpp"

#include "Shapes/Aabb2d.hpp"
#include "Shapes/Box2d.hpp"
#include "Shapes/Circle2d.hpp"
#include "Collision/Mesh2d.hpp"
#include "Collision/PrimitiveGeometry2d.hpp"
#include "Collision/Sat2d.hpp"
#include "Manifold2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------SimpleIntersection
bool SimpleIntersection::PointAabb(const Vector2& point, const Aabb2d& aabb)
{
  return PrimitiveGeometry2d::PointAabb(point, aabb.mMin, aabb.mMax);
}

bool SimpleIntersection::AabbCircle(const Aabb2d& aabb0, const Circle2d& circle1, Manifold2d& manifold)
{
  // If we have deep penetration (the circle center is in the aabb), then we have to build the manifold differently
  if(PointAabb(circle1.mCenter, aabb0))
  {
    manifold.mPointCount = 1;
    ManifoldPoint2d& point = manifold.mPoints[0];

    // To handle deep penetration, we need to find which axis requires the least effort to push the aabb center out of.
    // To do this, find how far away the circle center is from the aabb center and use
    // this with the aabb's half extents to compute the distance to each axis' edge.
    Vector2 aabbCenter = aabb0.GetCenter();
    Vector2 halfExtents = aabb0.GetHalfExtents();
    Vector2 aabbToCircle = circle1.mCenter - aabbCenter;
    Vector2 absAabbToCircle = Math::Abs(aabbToCircle);
    Vector2 distancesToAabbSurface = halfExtents - absAabbToCircle;

    size_t axisOfLeastOverlap = 0;
    if(distancesToAabbSurface.y <= distancesToAabbSurface.x)
      axisOfLeastOverlap = 1;

    // The axis of least overlap is the collision normal
    point.mNormal = Vector2::cZero;
    point.mNormal[axisOfLeastOverlap] = static_cast<float>(Math::Sign(aabbToCircle[axisOfLeastOverlap]));
    // The penetration distance is the shortest distance to the surface plus the circle radius (since the circle is completely inside the aabb)
    point.mPenetrationDistance = circle1.mRadius + distancesToAabbSurface[axisOfLeastOverlap];
    // The point on the circle is just the point in the direction of the normal
    point.mPoint1 = circle1.mCenter - point.mNormal * circle1.mRadius;
    // The point on the aabb is just the one in the opposite direction of the normal, but the full penetration distance away
    point.mPoint0 = point.mPoint1 + point.mNormal * point.mPenetrationDistance;
    return true;
  }

  // Otherwise this is a shallow penetration. Project the circle center onto the aabb.
  // If the projected point is within the circle then there's intersection.
  Vector2 clampedCircleCenter = Math::Clamp(circle1.mCenter, aabb0.mMin, aabb0.mMax);
  float distSq = Math::DistanceSq(circle1.mCenter, clampedCircleCenter);
  float radiusSq = Math::Sq(circle1.mRadius);
  if(distSq > radiusSq)
    return false;

  manifold.mPointCount = 1;
  ManifoldPoint2d& point = manifold.mPoints[0];

  // The vector from the projected point to the circle center is the normal.
  // We can use the normal to then compute the two points.
  point.mNormal = Math::Normalized(circle1.mCenter - clampedCircleCenter);
  point.mPoint0 = clampedCircleCenter;
  point.mPoint1 = circle1.mCenter - point.mNormal * circle1.mRadius;
  point.mPenetrationDistance = -Math::Dot(point.mPoint1 - point.mPoint0, point.mNormal);

  return true;
}

bool SimpleIntersection::BoxBox(const Box2d& box0, const Box2d& box1, Manifold2d& manifold)
{
  Box2dMesh boxMesh0(box0);
  Box2dMesh boxMesh1(box1);
  Sat2d sat;
  return sat.Test(boxMesh0, boxMesh1, &manifold);
}

bool SimpleIntersection::BoxCircle(const Box2d& box0, const Circle2d& circle1, Manifold2d& manifold)
{
  Matrix2 localToWorldRotation = box0.mRotation;
  Matrix2 worldToLocalRotation = localToWorldRotation.Transposed();
  // Transform the box to an aabb where it's center is at the origin
  Aabb2d localAabb0 = Aabb2d::FromCenterAndHalfExtents(Vector2::cZero, box0.mHalfExtents);
  // Perform the same translation on the circle, so now we have aabb vs circle
  Circle2d localCircle1 = circle1;
  localCircle1.mCenter = Math::Multiply(worldToLocalRotation, localCircle1.mCenter - box0.mCenter);

  if(!AabbCircle(localAabb0, localCircle1, manifold))
    return false;

  // Transform the data back into world space
  for(size_t i = 0; i < manifold.mPointCount; ++i)
  {
    ManifoldPoint2d& point = manifold.mPoints[i];
    point.mPoint0 = Math::Multiply(localToWorldRotation, point.mPoint0) + box0.mCenter;
    point.mPoint1 = Math::Multiply(localToWorldRotation, point.mPoint1) + box0.mCenter;
    point.mNormal = Math::Multiply(localToWorldRotation, point.mNormal);
  }

  return true;
}

bool SimpleIntersection::CircleCircle(const Circle2d& circle0, const Circle2d& circle1, Manifold2d& manifold)
{
  Vector2 separationVector = circle1.mCenter - circle0.mCenter;
  float radiiSum = circle1.mRadius + circle0.mRadius;
  float radiiSumSq = Math::Sq(radiiSum);
  float distSq = Math::LengthSq(separationVector);
  if(distSq > radiiSumSq)
    return false;

  manifold.mPointCount = 1;
  ManifoldPoint2d& point = manifold.mPoints[0];

  float dist = Math::Sqrt(distSq);
  point.mNormal = separationVector / dist;
  point.mPenetrationDistance = radiiSum - dist;
  point.mPoint0 = circle0.mCenter + point.mNormal * circle0.mRadius;
  point.mPoint1 = circle1.mCenter - point.mNormal * circle1.mRadius;
  return true;
}

bool SimpleIntersection::TestIntersection(const Vector2& point, const Aabb2d& aabb)
{
  return PointAabb(point, aabb);
}

bool SimpleIntersection::TestIntersection(const Aabb2d& aabb0, const Circle2d& circle1, Manifold2d& manifold)
{
  return AabbCircle(aabb0, circle1, manifold);
}

bool SimpleIntersection::TestIntersection(const Box2d& box0, const Box2d& box1, Manifold2d& manifold)
{
  return BoxBox(box0, box1, manifold);
}

bool SimpleIntersection::TestIntersection(const Box2d& box0, const Circle2d& circle1, Manifold2d& manifold)
{
  return BoxCircle(box0, circle1, manifold);
}

bool SimpleIntersection::TestIntersection(const Circle2d& circle0, const Circle2d& circle1, Manifold2d& manifold)
{
  return CircleCircle(circle0, circle1, manifold);
}

}//namespace Physics2d
