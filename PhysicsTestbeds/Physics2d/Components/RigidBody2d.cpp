#include "Precompiled.hpp"

#include "RigidBody2d.hpp"

#include "Engine/Cog.hpp"
#include "Engine/Space.hpp"

#include "PhysicsSpace2d.hpp"
#include "ZeroUtilities.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------RigidBody2d
ZilchDefineType(RigidBody2d, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  ZilchBindGetterSetterProperty(IsStatic);
  ZilchBindGetterSetterProperty(LinearVelocity)->ZeroSerialize(Vector2::cZero);
  ZilchBindGetterSetterProperty(AngularVelocity)->ZeroSerialize(0.0f);
  ZilchBindFieldProperty(mInvMass)->ZeroSerialize(1.0f);
  ZilchBindFieldProperty(mInvInertia)->ZeroSerialize(1.0f);
}

void RigidBody2d::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void RigidBody2d::Initialize(Zero::CogInitializer& initializer)
{
  mSpace = GetSpace()->has(PhysicsSpace2d);
  if(mSpace == nullptr)
    return;
  mSpace->Add(this);

  ReadTransform();
}

void RigidBody2d::TransformUpdate(Zero::TransformUpdateInfo& info)
{
  bool isPhysicsUpdate = (info.TransformFlags & Zero::TransformUpdateFlags::Physics) != 0;
  if(!isPhysicsUpdate)
    ReadTransform();
}

void RigidBody2d::OnDestroy(uint flags)
{
  if(mSpace == nullptr)
    return;
  mSpace->Remove(this);
}

bool RigidBody2d::GetIsStatic() const
{
  return mIsStatic;
}

void RigidBody2d::SetIsStatic(bool isStatic)
{
  mIsStatic = isStatic;
  if(mSpace != nullptr)
    mSpace->UpdateRigidBodyDynamicState(this);
}

float RigidBody2d::GetInvMass() const
{
  if(mIsStatic)
    return 0.0f;
  return mInvMass;
}

float RigidBody2d::GetInvInertia() const
{
  if(mIsStatic)
    return 0.0f;
  return mInvInertia;
}

Vector2 RigidBody2d::GetWorldCenterOfMass() const
{
  return mWorldCenterOfMass;
}

float RigidBody2d::GetWorldRotation() const
{
  return mWorldRotation;
}

Vector2 RigidBody2d::GetLinearVelocity() const
{
  return mLinearVelocity;
}

void RigidBody2d::SetLinearVelocity(const Vector2& linearVelocity)
{
  mLinearVelocity = linearVelocity;
}

float RigidBody2d::GetAngularVelocity() const
{
  return mAngularVelocity;
}

void RigidBody2d::SetAngularVelocity(float angularVelocity)
{
  mAngularVelocity = angularVelocity;
}

void RigidBody2d::GetVelocities(Vector2& linearVelocity, float& angularVelocity) const
{
  linearVelocity = mLinearVelocity;
  angularVelocity = mAngularVelocity;
}

void RigidBody2d::SetVelocities(const Vector2& linearVelocity, float angularVelocity)
{
  mLinearVelocity = linearVelocity;
  mAngularVelocity = angularVelocity;
}

void RigidBody2d::ReadTransform()
{
  Zero::Transform* transform = GetOwner()->has(Zero::Transform);
  mWorldCenterOfMass = ZeroUtilities::GetWorldTranslation(transform);
  mWorldRotation = ZeroUtilities::GetWorldRotation(transform);
}

}//namespace Physics2d
