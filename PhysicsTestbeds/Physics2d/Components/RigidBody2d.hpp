#pragma once

#include "Physics2dStandard.hpp"

namespace Physics2d
{

class PhysicsSpace2d;
class Physics2dNode;

//-------------------------------------------------------------------RigidBody2d
class RigidBody2d : public Zero::Component
{
public:
  ZilchDeclareType(RigidBody2d, TypeCopyMode::ReferenceType);

  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer) override;
  void TransformUpdate(Zero::TransformUpdateInfo& info) override;
  void OnDestroy(uint flags = 0) override;

  bool GetIsStatic() const;
  void SetIsStatic(bool isStatic);

  // Masses ------------------------
  float GetInvMass() const;
  void SetInvMass(float invMass);

  float GetInvInertia() const;
  void SetInvInertia(float invInertia);

  Vector2 GetWorldCenterOfMass() const;
  void SetWorldCenterOfMass(const Vector2& worldCenterOfMass);

  float GetWorldRotation() const;

  // Velocities ------------------------
  Vector2 GetLinearVelocity() const;
  void SetLinearVelocity(const Vector2& linearVelocity);

  float GetAngularVelocity() const;
  void SetAngularVelocity(float angularVelocity);

  void GetVelocities(Vector2& linearVelocity, float& angularVelocity) const;
  void SetVelocities(const Vector2& linearVelocity, float angularVelocity);

  // Internal ------------------------
  void SetNode(Physics2dNode* node);
  Physics2dNode* GetNode();

private:
  friend PhysicsSpace2d;

  void ReadTransform();

  PhysicsSpace2d* mSpace = nullptr;
  Zero::Link<RigidBody2d> mSpaceLink;
  Physics2dNode* mNode = nullptr;

  bool mIsStatic = false;

  float mInvMass = 1.0f;
  float mInvInertia = 1.0f;
  Vector2 mForce = Vector2::cZero;
  float mTorque = 0.0f;
  Vector2 mLinearVelocity = Vector2::cZero;
  float mAngularVelocity = 0.0f;
  Vector2 mWorldCenterOfMass = Vector2::cZero;
  float mWorldRotation = 0.0f;
};

}//namespace Physics2d
