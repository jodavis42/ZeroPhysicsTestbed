#pragma once

#include "Physics2dStandard.hpp"

#include "Collider2d.hpp"
#include "Shapes/Box2d.hpp"

namespace Physics2d
{

class PhysicsSpace2d;

//-------------------------------------------------------------------BoxCollider2d
class BoxCollider2d : public Collider2d
{
public:
  ZilchDeclareType(BoxCollider2d, TypeCopyMode::ReferenceType);
  BoxCollider2d();
  
  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer) override;
  void OnDestroy(uint flags = 0) override;
  void DebugDraw() override;

  float GetLocalArea() const override;

  Vector2 GetWorldSize() const;
  Box2d ToShape() const;

private:
  void UpdateBoundingVolumes() override;

  Vector2 GetLocalHalfExtents() const;
  Aabb2d GetLocalAabb() const override;
  Circle2d GetLocalCircle() const override;

  Vector2 mSize;
};

}//namespace Physics2d
