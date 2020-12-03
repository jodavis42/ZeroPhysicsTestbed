#pragma once

#include "Physics2dStandard.hpp"

#include "Engine/CogPath.hpp"
#include "Engine/Component.hpp"
#include "CollisionDetection/ContactManifold2d.hpp"

namespace Zero
{
class UpdateEvent;
}

namespace Physics2d
{

class Collider2d;

//-------------------------------------------------------------------CollisionDebug
class CollisionDebug : public Zero::Component
{
public:
  ZilchDeclareType(CollisionDebug, TypeCopyMode::ReferenceType);

  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer);
  void OnAllObjectsCreated(Zero::CogInitializer& initializer);
  void OnFrameUpdate(Zero::UpdateEvent* e);

private:
  void DrawManifolds(const Array<ContactManifold2d>& manifolds) const;

  bool mActive = true;
  Zero::CogPath mPath0;
  Zero::CogPath mPath1;

  bool mOnTop = true;
  Vector4 mPoint0Color = Vector4::cZero;
  Vector4 mPoint1Color = Vector4::cZero;
  Vector4 mNormalColor = Vector4::cZero;
  Vector4 mPenetrationDistanceColor = Vector4::cZero;

  float mPointSize = 0.1f;
  float mNormalHeadSize = 0.1f;
};

}//namespace Physics2d
