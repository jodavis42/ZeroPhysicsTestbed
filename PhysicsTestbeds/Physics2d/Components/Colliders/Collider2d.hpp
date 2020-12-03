#pragma once

#include "Physics2dStandard.hpp"
#include "Physics2dCore/SpatialPartitions/SpatialPartitionData.hpp"
#include "Physics2dCore/Shapes/Aabb2d.hpp"
#include "Physics2dCore/Shapes/Circle2d.hpp"

namespace Physics2d
{

class PhysicsSpace2d;
class Physics2dMaterial;

enum class Collider2dType { None = -1, Box = 0, Circle, Size };

//-------------------------------------------------------------------Collider2d
class Collider2d : public Zero::Component
{
public:
  ZilchDeclareType(Collider2d, TypeCopyMode::ReferenceType);

  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer) override;
  void OnDestroy(uint flags = 0) override;
  void DebugDraw() override;

  Collider2dType GetType() const;
  virtual float GetLocalArea() const;

  Aabb2d GetWorldAabb() const;
  Circle2d GetWorldCircle() const;

  bool GetIsGhost() const;
  void SetIsGhost(bool isGhost);

  float GetDensity() const;
  float GetRestitution() const;
  float GetDynamicFriction() const;

  virtual void UpdateBoundingVolumes();

protected:
  friend PhysicsSpace2d;

  virtual Aabb2d GetLocalAabb() const;
  virtual Circle2d GetLocalCircle() const;
  void ComputeWorldAabb(const Matrix3& worldTransform2d, const Aabb2d& localAabb);
  void ComputeWorldCircle(const Matrix3& worldTransform2d, const Circle2d& localCircle);

  Collider2dType mColliderType = Collider2dType::None;

  PhysicsSpace2d* mSpace = nullptr;
  Zero::Link<Collider2d> mSpaceLink;

  SpatialPartitionKey mSpatialPartitionKey;
  Aabb2d mWorldAabb;
  Circle2d mWorldCircle;

  HandleOf<Physics2dMaterial> mMaterial;
  bool mIsGhost = false;
};

}//namespace Physics2d
