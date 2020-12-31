#include "Precompiled.hpp"

#include "Components/Colliders/CircleCollider2d.hpp"

#include "Components/PhysicsSpace2d.hpp"
#include "Utilities/ZeroUtilities.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------CircleCollider2d
ZilchDefineType(CircleCollider2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  ZeroBindInterface(Collider2d);

  ZilchBindFieldProperty(mRadius)->ZeroSerialize(0.5f);
}

CircleCollider2d::CircleCollider2d()
{
  mColliderType = Collider2dType::Circle;
}

void CircleCollider2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void CircleCollider2d::Initialize(Zero::CogInitializer& initializer)
{
  Collider2d::Initialize(initializer);
}

void CircleCollider2d::OnDestroy(uint flags)
{
  Collider2d::OnDestroy(flags);
}

void CircleCollider2d::DebugDraw()
{
  Collider2d::DebugDraw();

  Circle2d circle = ToShape();
  Vector3 center = Math::ToVector3(circle.mCenter, 0.0f);
  Zero::gDebugDraw->Add(Zero::Debug::Circle(center, Math::Vector3::cZAxis, circle.mRadius));
}

float CircleCollider2d::GetLocalArea() const
{
  return Math::cPi * mRadius * mRadius;
}

Collider2dMassData CircleCollider2d::ComputeMassData() const
{
  float worldRadius = GetWorldRadius();
  Collider2dMassData result;
  result.mLocalCenterOfMass = Vector2::cZero;
  result.mDensity = GetDensity();
  result.mWorldArea = Math::cPi * worldRadius * worldRadius;
  result.mWorldMass = result.mDensity * result.mWorldArea;
  result.mWorldInertia = result.mWorldMass * (0.5f * Math::Sq(worldRadius) + Math::Dot(result.mLocalCenterOfMass, result.mLocalCenterOfMass));
  return result;
}

float CircleCollider2d::GetWorldRadius() const 
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);
  Vector2 worldScale = ZeroUtilities::GetWorldScale(transform);
  float maxScale = Math::Max(worldScale.x, worldScale.y);
  return maxScale * mRadius;
}

Circle2d CircleCollider2d::ToShape() const
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);
  Matrix3 worldTransform2d = ZeroUtilities::ToWorldTransform2d(transform);
  Circle2d localCircle = GetLocalCircle();
  Circle2d worldCircle = localCircle.Transform(worldTransform2d);
  return worldCircle;
}

void CircleCollider2d::UpdateBoundingVolumes()
{
  // The world circle is just our shape. the world aabb is just the aabb of this circle (doesn't change when we rotate).
  mWorldCircle = ToShape();
  mWorldAabb = Aabb2d::FromCenterAndHalfExtents(mWorldCircle.mCenter, Vector2(mWorldCircle.mRadius));
}

Aabb2d CircleCollider2d::GetLocalAabb() const
{
  return Aabb2d::FromCenterAndHalfExtents(Vector2::cZero, Vector2(mRadius, mRadius));
}

Circle2d CircleCollider2d::GetLocalCircle() const
{
  return Circle2d(Vector2::cZero, mRadius);
}

}//namespace Physics2d
