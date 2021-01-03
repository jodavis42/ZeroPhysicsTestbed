#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"
#include "Physics2dCore/Shapes/Box2d.hpp"

namespace Physics2d
{

class Box2d;

//-------------------------------------------------------------------Mesh2dFace
class Mesh2dFace
{
public:
  Vector2 mPoint0;
  Vector2 mPoint1;
  Vector2 mNormal;
};

//-------------------------------------------------------------------Mesh2d
class Mesh2d
{
public:
  virtual Vector2 Search(const Vector2& direction) const;

  size_t GetVertexCount() const;
  Vector2 GetVertex(size_t vertexIndex) const;

  size_t GetFaceCount() const;
  void GetFace(size_t index, Mesh2dFace& face) const;

  void GetEdgeVertices(size_t index, Vector2& p0, Vector2& p1) const;

protected:
  size_t mVertexCount = 0;
  Vector2* mVertices = nullptr;
};

//-------------------------------------------------------------------Box2dMesh
class Box2dMesh : public Mesh2d
{
public:
  Box2dMesh(const Box2d& box);

  Vector2 Search(const Vector2& direction) const override;

  Vector2 mBoxVertices[4];
  Box2d mBox;
};

}//namespace Physics2d
