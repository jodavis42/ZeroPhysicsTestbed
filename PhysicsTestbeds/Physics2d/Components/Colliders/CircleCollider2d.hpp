#pragma once

#include "Physics2dStandard.hpp"

#include "Collider2d.hpp"
#include "Shapes/Circle2d.hpp"

namespace Physics2d
{

class PhysicsSpace2d;

//-------------------------------------------------------------------CircleCollider2d
class CircleCollider2d : public Collider2d
{
public:
  ZilchDeclareType(CircleCollider2d, TypeCopyMode::ReferenceType);
  CircleCollider2d();
  
  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer) override;
  void OnDestroy(uint flags = 0) override;
  void DebugDraw() override;

  float GetLocalArea() const override;

  float GetWorldRadius() const;
  Circle2d ToShape() const;

private:
  void UpdateBoundingVolumes() override;
  Aabb2d GetLocalAabb() const override;
  Circle2d GetLocalCircle() const override;

  friend PhysicsSpace2d;

  float mRadius = 0.5f;
};

}//namespace Physics2d
