#include "Precompiled.hpp"

#include "Mesh2d.hpp"

#include "Shapes/Box2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Mesh2d
Vector2 Mesh2d::Search(const Vector2& direction) const
{
  float maxProj = -Math::PositiveMax();
  Vector2 result = Vector2::cZero;;
  for(size_t i = 0; i < mVertexCount; ++i)
  {
    float proj = Math::Dot(direction, mVertices[i]);
    if(proj > maxProj)
    {
      maxProj = proj;
      result = mVertices[i];
    }
  }
  return result;
}

size_t Mesh2d::GetVertexCount() const
{
  return mVertexCount;
}

Vector2 Mesh2d::GetVertex(size_t vertexIndex) const
{
  ErrorIf(vertexIndex >= mVertexCount, "Invalid index");
  return mVertices[vertexIndex];
}

size_t Mesh2d::GetFaceCount() const
{
  return GetVertexCount();
}

void Mesh2d::GetFace(size_t index, Mesh2dFace& face) const
{
  GetEdgeVertices(index, face.mPoint0, face.mPoint1);
  Vector2 edge = face.mPoint1 - face.mPoint0;
  face.mNormal = Vector2(edge.y, -edge.x);
  face.mNormal = Math::Normalized(face.mNormal);
}

void Mesh2d::GetEdgeVertices(size_t index, Vector2& p0, Vector2& p1) const
{
  p0 = mVertices[index % mVertexCount];
  p1 = mVertices[(index + 1) % mVertexCount];
}

//-------------------------------------------------------------------Box2dMesh
Box2dMesh::Box2dMesh(const Box2d& box)
{
  mVertexCount = 4;
  mVertices = mBoxVertices;
  mBoxVertices[0] = box.mCenter + box.mRotation.GetBasis(0) * box.mHalfExtents.x + box.mRotation.GetBasis(1) * box.mHalfExtents.y;
  mBoxVertices[1] = box.mCenter - box.mRotation.GetBasis(0) * box.mHalfExtents.x + box.mRotation.GetBasis(1) * box.mHalfExtents.y;
  mBoxVertices[2] = box.mCenter - box.mRotation.GetBasis(0) * box.mHalfExtents.x - box.mRotation.GetBasis(1) * box.mHalfExtents.y;
  mBoxVertices[3] = box.mCenter + box.mRotation.GetBasis(0) * box.mHalfExtents.x - box.mRotation.GetBasis(1) * box.mHalfExtents.y;
  mBox = box;
}

Vector2 Box2dMesh::Search(const Vector2& direction) const
{
  return mBox.Search(direction);
}

}//namespace Physics2d
