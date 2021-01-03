#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

class Mesh2d;
class Mesh2dFace;
class Manifold2d;
class Plane2d;

//-------------------------------------------------------------------Sat2d
class Sat2d
{
public:
  bool Test(const Mesh2d& mesh0, const Mesh2d& mesh1, Manifold2d* manifold);

private:
  struct SatFaceData
  {
    static constexpr size_t InvalidIndex = static_cast<size_t>(-1);
    size_t mFaceOfSeparation = InvalidIndex;
    size_t mFaceOfMinPenetration = InvalidIndex;
    float mMinPenetration = Math::PositiveMax();
  };
  bool TestFaces(const Mesh2d& primaryMesh, const Mesh2d& secondaryMesh, SatFaceData& faceData)const;
  void ComputeContact(const Mesh2d& referenceMesh, const Mesh2d& incidentMesh, SatFaceData& referenceFaceData, Manifold2d& manifold)const;
  void FindIncidentFace(const Mesh2d& mesh, const Vector2& referenceNormal, Mesh2dFace& incidentFace) const;
  void ClipIncidentFace(const Mesh2dFace& referenceFace, Mesh2dFace& incidentFace) const;
  void ClipFaceToPlane(const Plane2d& plane, Vector2& point0, Vector2& point1) const;
};

}//namespace Physics2d
