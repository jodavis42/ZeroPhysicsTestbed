#include "Precompiled.hpp"

#include "Components/Colliders/BoxCollider2d.hpp"

#include "Engine/Cog.hpp"
#include "Engine/Space.hpp"

#include "Components/PhysicsSpace2d.hpp"
#include "Utilities/ZeroUtilities.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------BoxCollider2d
ZilchDefineType(BoxCollider2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  ZeroBindInterface(Collider2d);

  ZilchBindFieldProperty(mSize)->ZeroSerialize(Vector2(1));
}

BoxCollider2d::BoxCollider2d()
{
  mColliderType = Collider2dType::Box;
}

void BoxCollider2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void BoxCollider2d::Initialize(Zero::CogInitializer& initializer)
{
  Collider2d::Initialize(initializer);
}

void BoxCollider2d::OnDestroy(uint flags)
{
  Collider2d::OnDestroy(flags);
}

void BoxCollider2d::DebugDraw()
{
  Collider2d::DebugDraw();

  Box2d box = ToShape();
  Vector3 center = Math::ToVector3(box.mCenter, 0.0f);
  Vector2 halfExtents = box.mHalfExtents;
  Quaternion rotation = ZeroUtilities::ToQuaternion(box.mRotation);
  Zero::gDebugDraw->Add(Zero::Debug::Box(center, halfExtents, rotation));
}

float BoxCollider2d::GetLocalArea() const
{
  return mSize.x * mSize.y;
}

Vector2 BoxCollider2d::GetWorldSize() const
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);
  Vector2 worldScale = ZeroUtilities::GetWorldScale(transform);
  return mSize * worldScale;
}

Box2d BoxCollider2d::ToShape() const
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);
  
  Vector2 worldScale, worldTranslation;
  float worldRotation;
  ZeroUtilities::ToWorldTransform2d(transform, worldScale, worldRotation, worldTranslation);
  Matrix3 worldTransform2d = Matrix3::GenerateTransform(worldTranslation, worldRotation, worldScale);

  Box2d result;
  result.mCenter = Math::TransformPoint(worldTransform2d, Vector2::cZero);
  result.mHalfExtents = GetLocalHalfExtents() * worldScale;
  result.mRotation.Rotate(worldRotation);
  return result;
}

void BoxCollider2d::UpdateBoundingVolumes()
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);

  Vector2 worldScale, worldTranslation;
  float worldRotation;
  ZeroUtilities::ToWorldTransform2d(transform, worldScale, worldRotation, worldTranslation);
  Matrix3 worldTransform2d = Matrix3::GenerateTransform(worldTranslation, worldRotation, worldScale);
  Vector2 obbWorldHalfExtents = GetLocalHalfExtents() * worldScale;

  Aabb2d localAabb = GetLocalAabb();
  ComputeWorldAabb(worldTransform2d, localAabb);
  // Compute the circle from the world obb's half extents, not the aabb. This is so the circle doesn't resize when rotating.
  mWorldCircle.mCenter = mWorldAabb.GetCenter();
  mWorldCircle.mRadius = Math::Length(obbWorldHalfExtents);
}

Vector2 BoxCollider2d::GetLocalHalfExtents() const
{
  return mSize * 0.5f;
}

Aabb2d BoxCollider2d::GetLocalAabb() const
{
  return Aabb2d::FromCenterAndHalfExtents(Vector2::cZero, GetLocalHalfExtents());
}

Circle2d BoxCollider2d::GetLocalCircle() const
{
  float radius = Math::Length(GetLocalHalfExtents());
  return Circle2d(Vector2::cZero, radius);
}

}//namespace Physics2d
