#include "Precompiled.hpp"

#include "Sat2d.hpp"

#include "Collision/Mesh2d.hpp"
#include "Manifold2d.hpp"
#include "PrimitiveGeometry2d.hpp"
#include "Shapes/Plane2d.hpp"
#include "Shapes/Ray2d.hpp"

namespace Physics2d
{

bool Sat2d::Test(const Mesh2d& mesh0, const Mesh2d& mesh1, Manifold2d* manifold)
{
  SatFaceData faceData0, faceData1;
  if(!TestFaces(mesh0, mesh1, faceData0))
    return false;
  if(!TestFaces(mesh1, mesh0, faceData1))
    return false;

  if(manifold == nullptr)
    return true;
  
  if(faceData0.mMinPenetration < faceData1.mMinPenetration)
  {
    ComputeContact(mesh0, mesh1, faceData0, *manifold);
  }
  else
  {
    ComputeContact(mesh1, mesh0, faceData1, *manifold);
    manifold->Flip();
  }
  
  return true;
}

bool Sat2d::TestFaces(const Mesh2d& primaryMesh, const Mesh2d& secondaryMesh, SatFaceData& faceData) const
{
  // Test every face on the primary mesh to see if there's separation
  faceData.mMinPenetration = Math::PositiveMax();
  faceData.mFaceOfMinPenetration = SatFaceData::InvalidIndex;

  for(size_t faceIndex = 0; faceIndex < primaryMesh.GetFaceCount(); ++faceIndex)
  {
    Mesh2dFace face;
    primaryMesh.GetFace(faceIndex, face);
    // On the secondary mesh, find the vertex furthest in the opposite direction of the face normal on the primary mesh.
    Vector2 secondaryPoint = secondaryMesh.Search(-face.mNormal);
    // If this vertex is in front of the face, then there's no overlap and the shapes are separating on this axis
    float penetration = Math::Dot(face.mPoint0 - secondaryPoint, face.mNormal);
    if(penetration < 0)
    {
      faceData.mFaceOfSeparation = faceIndex;
      return false;
    }

    // Otherwise, keep track of the face with the least penetration
    if(penetration < faceData.mMinPenetration)
    {
      faceData.mMinPenetration = penetration;
      faceData.mFaceOfMinPenetration = faceIndex;
    }
  }
  // If no face is separating, then there's a potential collision
  return true;
}

void Sat2d::ComputeContact(const Mesh2d& referenceMesh, const Mesh2d& incidentMesh, SatFaceData& referenceFaceData, Manifold2d& manifold) const
{
  Mesh2dFace referenceFace;
  referenceMesh.GetFace(referenceFaceData.mFaceOfMinPenetration, referenceFace);

  Mesh2dFace incidentFace;
  FindIncidentFace(incidentMesh, referenceFace.mNormal, incidentFace);

  ClipIncidentFace(referenceFace, incidentFace);
  
  Plane2d referencePlane = Plane2d::FromPointAndNormal(referenceFace.mPoint0, referenceFace.mNormal);
  Vector2 clippedPoints[2] = {incidentFace.mPoint0, incidentFace.mPoint1};
  manifold.mPointCount = 0;
  for(size_t i = 0; i < 2; ++i)
  {
    IntersectionType::Type clippedPointType = PrimitiveGeometry2d::PointPlane(clippedPoints[i], referencePlane.GetData(), 0.0f);
    if(clippedPointType == IntersectionType::Inside)
      continue;

    ManifoldPoint2d& point = manifold.mPoints[manifold.mPointCount];
    point.mNormal = referenceFace.mNormal;
    point.mPenetrationDistance = -Math::Dot(clippedPoints[i] - referenceFace.mPoint0, point.mNormal);
    point.mPoint1 = clippedPoints[i];
    point.mPoint0 = point.mPoint1 + point.mNormal * point.mPenetrationDistance;
    ++manifold.mPointCount;
  }
}

void Sat2d::FindIncidentFace(const Mesh2d& mesh, const Vector2& referenceNormal, Mesh2dFace& incidentFace) const
{
  // To find the incident face, we need to find the face on the given mesh that is most anti-parallel.
  // That is, find the face with the most negative dot product given our reference normal.
  float minCosTheta = 0.0f;
  for(size_t secondaryFaceIndex = 0; secondaryFaceIndex < mesh.GetFaceCount(); ++secondaryFaceIndex)
  {
    Mesh2dFace face;
    mesh.GetFace(secondaryFaceIndex, face);

    float cosTheta = Math::Dot(face.mNormal, referenceNormal);
    if(cosTheta < minCosTheta)
    {
      minCosTheta = cosTheta;
      incidentFace = face;
    }
  }
}

void Sat2d::ClipIncidentFace(const Mesh2dFace& referenceFace, Mesh2dFace& incidentFace) const
{
  Vector2 referenceEdgeNormal01 = Math::AttemptNormalized(referenceFace.mPoint1 - referenceFace.mPoint0);
  Plane2d plane01 = Plane2d::FromPointAndNormal(referenceFace.mPoint0, referenceEdgeNormal01);
  Plane2d plane10 = Plane2d::FromPointAndNormal(referenceFace.mPoint1, -referenceEdgeNormal01);
  ClipFaceToPlane(plane01, incidentFace.mPoint0, incidentFace.mPoint1);
  ClipFaceToPlane(plane10, incidentFace.mPoint0, incidentFace.mPoint1);
}

void Sat2d::ClipFaceToPlane(const Plane2d& plane, Vector2& point0, Vector2& point1) const
{
  Vector3 planeData = plane.GetData();
  // Classify both points against the plane
  IntersectionType::Type p0Type = PrimitiveGeometry2d::PointPlane(point0, planeData, 0.0f);
  IntersectionType::Type p1Type = PrimitiveGeometry2d::PointPlane(point1, planeData, 0.0f);

  auto computeIntersectionPoint = [](const Vector3& planeData, const Vector2& point0, Vector2& point1) -> Vector2
  {
    float t;
    Ray2d ray = Ray2d::From2Points(point0, point1);
    PrimitiveGeometry2d::RayPlane(ray.GetStart(), ray.GetDirection(), planeData, t);
    return ray.GetPoint(t);
  };

  if(p0Type == IntersectionType::Outside)
  {
    point0 = computeIntersectionPoint(planeData, point0, point1);
    if(p1Type == IntersectionType::Outside)
      point1 = point0;
  }
  else if(p0Type == IntersectionType::Coplanar)
  {
    if(p1Type == IntersectionType::Outside)
      point1 = computeIntersectionPoint(planeData, point0, point1);
  }
  else if(p0Type == IntersectionType::Inside)
  {
    if(p1Type == IntersectionType::Outside)
      point1 = computeIntersectionPoint(planeData, point0, point1);
  }
}

}//namespace Physics2d
