#include "Precompiled.hpp"

#include "Components/Colliders/Collider2d.hpp"

#include "Engine/Space.hpp"

#include "Components/PhysicsSpace2d.hpp"
#include "Components/Physics2dDebugDrawConfig.hpp"
#include "Resources/Physics2dMaterial.hpp"
#include "Utilities/ZeroUtilities.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Collider2d
ZilchDefineType(Collider2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  ZilchBindFieldProperty(mMaterial);
  ZilchBindGetterSetterProperty(IsGhost);
}

void Collider2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void Collider2d::Initialize(Zero::CogInitializer& initializer)
{
  mSpace = GetSpace()->has(PhysicsSpace2d);
  if(mSpace == nullptr)
    return;
  mSpace->Add(this);
}

void Collider2d::OnDestroy(uint flags)
{
  if(mSpace == nullptr)
    return;
  mSpace->Remove(this);
}

void Collider2d::DebugDraw()
{
  UpdateBoundingVolumes();

  Physics2dDebugDrawConfig* debugDrawConfig = Physics2dDebugDrawConfig::GetConfig(mSpace);
  Zero::Debug::Box debugBox = Zero::Debug::Box(Math::ToVector3(mWorldAabb.GetCenter(), 0.0f), mWorldAabb.GetHalfExtents());
  Zero::Debug::Circle debugCircle = Zero::Debug::Circle(Math::ToVector3(mWorldCircle.mCenter, 0.0f), Vector3::cZAxis, mWorldCircle.mRadius);
  if(debugDrawConfig != nullptr)
  {
    if(debugDrawConfig->mDrawColliderAabbs)
      Zero::gDebugDraw->Add(debugBox.Color(debugDrawConfig->mColliderAabbColor));
    if(debugDrawConfig->mDrawColliderCircles)
      Zero::gDebugDraw->Add(debugCircle.Color(debugDrawConfig->mColliderCircleColor));
  }
  else
  {
    Zero::gDebugDraw->Add(debugBox);
    Zero::gDebugDraw->Add(debugCircle);
  }
}

Collider2dType Collider2d::GetType() const
{
  return mColliderType;
}

float Collider2d::GetLocalArea() const
{
  return 1.0f;
}

Aabb2d Collider2d::GetWorldAabb() const
{
  return mWorldAabb;
}

Circle2d Collider2d::GetWorldCircle() const
{
  return mWorldCircle;
}

bool Collider2d::GetIsGhost() const
{
  return mIsGhost;
}

void Collider2d::SetIsGhost(bool isGhost)
{
  mIsGhost = isGhost;
}

float Collider2d::GetDensity() const
{
  Physics2dMaterial* material = mMaterial;
  if(material != nullptr)
    return material->mDensity;
  return 1.0f;
}

float Collider2d::GetRestitution() const
{
  Physics2dMaterial* material = mMaterial;
  if(material != nullptr)
    return material->mRestitution;
  return 0.25f;
}

float Collider2d::GetDynamicFriction() const
{
  Physics2dMaterial* material = mMaterial;
  if(material != nullptr)
    return material->mDynamicFriction;
  return 0.25f;
}

void Collider2d::UpdateBoundingVolumes()
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);
  Matrix3 worldTransform2d = ZeroUtilities::ToWorldTransform2d(transform);
  ComputeWorldAabb(worldTransform2d, GetLocalAabb());
  ComputeWorldCircle(worldTransform2d, GetLocalCircle());
}

Aabb2d Collider2d::GetLocalAabb() const
{
  return Aabb2d::FromCenterAndHalfExtents(Vector2::cZero, Vector2(0.5f));
}

Circle2d Collider2d::GetLocalCircle() const
{
  return Circle2d(Vector2::cZero, 0.5f);
}

void Collider2d::ComputeWorldAabb(const Matrix3& worldTransform2d, const Aabb2d& localAabb)
{
  mWorldAabb = localAabb.Transform(worldTransform2d);
}

void Collider2d::ComputeWorldCircle(const Matrix3& worldTransform2d, const Circle2d& localCircle)
{
  mWorldCircle = localCircle.Transform(worldTransform2d);
}

}//namespace Physics2d
