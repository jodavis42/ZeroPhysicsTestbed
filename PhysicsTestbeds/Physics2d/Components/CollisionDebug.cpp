#include "Precompiled.hpp"

#include "Components/CollisionDebug.hpp"

#include "Colliders/Collider2d.hpp"
#include "Components/PhysicsSpace2d.hpp"
#include "CollisionDetection/CollisionLibrary.hpp"

#include "Engine/Cog.hpp"
#include "Engine/Time.hpp"
#include "Engine/DebugDraw.hpp"
#include "Geometry/DebugDraw.hpp"
#include "Common/Math/ByteColor.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------CollisionDebug
ZilchDefineType(CollisionDebug, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  
  ZilchBindFieldProperty(mActive)->ZeroSerialize(false);
  ZilchBindFieldProperty(mPath0);
  ZilchBindFieldProperty(mPath1);

  ZilchBindFieldProperty(mOnTop)->ZeroSerialize(true);
  ZilchBindFieldProperty(mPoint0Color)->ZeroSerialize(ToFloatColor(Color::Red));
  ZilchBindFieldProperty(mPoint1Color)->ZeroSerialize(ToFloatColor(Color::Blue));
  ZilchBindFieldProperty(mNormalColor)->ZeroSerialize(ToFloatColor(Color::White));
  ZilchBindFieldProperty(mPenetrationDistanceColor)->ZeroSerialize(ToFloatColor(Color::Green));
  ZilchBindFieldProperty(mPointSize)->ZeroSerialize(0.1f);
  ZilchBindFieldProperty(mNormalHeadSize)->ZeroSerialize(0.1f);
}

void CollisionDebug::Serialize(Zero::Serializer& stream)
{
  SerializeNameDefault(mActive, false);
  stream.SerializeFieldDefault("Path0", mPath0, Zero::CogPath());
  stream.SerializeFieldDefault("Path1", mPath1, Zero::CogPath());

  SerializeNameDefault(mOnTop, true);
  SerializeNameDefault(mPoint0Color, ToFloatColor(Color::Red));
  SerializeNameDefault(mPoint1Color, ToFloatColor(Color::Blue));
  SerializeNameDefault(mNormalColor, ToFloatColor(Color::White));
  SerializeNameDefault(mPenetrationDistanceColor, ToFloatColor(Color::Green));
  SerializeNameDefault(mPointSize, 0.1f);
  SerializeNameDefault(mNormalHeadSize, 0.1f);
}

void CollisionDebug::Initialize(Zero::CogInitializer& initializer)
{
  ConnectThisTo(GetSpace(), Zero::Events::FrameUpdate, OnFrameUpdate);
}

void CollisionDebug::OnAllObjectsCreated(Zero::CogInitializer& initializer)
{
  mPath0.RestoreLink(initializer, this, "Path0");
  mPath1.RestoreLink(initializer, this, "Path1");
}

void CollisionDebug::OnFrameUpdate(Zero::UpdateEvent* e)
{
  if(!mActive)
    return;

  Collider2d* collider0 = mPath0.Has<Collider2d>();
  Collider2d* collider1 = mPath1.Has<Collider2d>();
  if(collider0 == nullptr || collider1 == nullptr)
    return;

  PhysicsSpace2d* physicsSpace = GetSpace()->has(PhysicsSpace2d);
  CollisionLibrary* collisionLibrary = physicsSpace->GetCollisionLibrary();

  Array<ContactManifold2d> manifolds;
  if(!collisionLibrary->TestPair(collider0, collider1, manifolds))
    return;
  
  DrawManifolds(manifolds);
}

void CollisionDebug::DrawManifolds(const Array<ContactManifold2d>& manifolds) const
{
  for(size_t i = 0; i < manifolds.Size(); ++i)
  {
    const ContactManifold2d& manifold = manifolds[i];
    for(size_t pointIndex = 0; pointIndex < manifold.mPointCount; ++pointIndex)
    {
      const ManifoldPoint2d& point = manifold.mPoints[pointIndex];
      Math::Vector3 p0 = Math::ToVector3(point.mPoint0, 0);
      Math::Vector3 p1 = Math::ToVector3(point.mPoint1, 0);
      Math::Vector3 penDistPoint = Math::ToVector3(point.mPoint0 - point.mNormal * point.mPenetrationDistance, 0);
      Zero::gDebugDraw->Add(Zero::Debug::Sphere(p0, mPointSize).Color(mPoint0Color).OnTop(mOnTop));
      Zero::gDebugDraw->Add(Zero::Debug::Sphere(p1, mPointSize).Color(mPoint1Color).OnTop(mOnTop));
      Zero::gDebugDraw->Add(Zero::Debug::Line(p0, p1).Color(mNormalColor).HeadSize(mNormalHeadSize).OnTop(mOnTop));
      Zero::gDebugDraw->Add(Zero::Debug::Line(p0, penDistPoint).Color(mPenetrationDistanceColor).HeadSize(mNormalHeadSize).OnTop(mOnTop));
    }
  }
}

}//namespace Physics2d
