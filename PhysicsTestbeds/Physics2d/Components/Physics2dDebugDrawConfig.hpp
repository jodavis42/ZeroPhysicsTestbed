#pragma once

#include "Physics2dStandard.hpp"

#include "Engine/Component.hpp"

namespace Physics2d
{

class PhysicsSpace2d;

//-------------------------------------------------------------------Physics2dDebugDrawConfig
class Physics2dDebugDrawConfig : public Zero::Component
{
public:
  ZilchDeclareType(Physics2dDebugDrawConfig, TypeCopyMode::ReferenceType);

  void Serialize(Zero::Serializer& stream) override;

  static Physics2dDebugDrawConfig* GetConfig(const PhysicsSpace2d* space);

  bool mDrawColliderAabbs = true;
  Vector4 mColliderAabbColor = Vector4(1);
  bool mDrawColliderCircles = true;
  Vector4 mColliderCircleColor = Vector4(1);
};

}//namespace Physics2d
