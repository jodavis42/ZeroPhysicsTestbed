#pragma once

#include "Physics2dStandard.hpp"
#include "Physics2dCore/SpatialPartitions/SpatialPartitionData.hpp"
#include "Physics2dCore/Shapes/Aabb2d.hpp"
#include "Physics2dCore/Shapes/Circle2d.hpp"

namespace Physics2d
{

class PhysicsSpace2d;
class Physics2dMaterial;
class Physics2dNode;

enum class Collider2dType { None = -1, Box = 0, Circle, Size };

struct Collider2dMassData
{
  Vector2 mLocalCenterOfMass = Vector2::cZero;
  float mDensity = 1.0f;
  float mWorldArea = 0.0f;
  float mWorldMass = 1.0f;
  float mWorldInertia = 0.0f;
};

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
  virtual Collider2dMassData ComputeMassData() const;

  Aabb2d GetWorldAabb() const;
  Circle2d GetWorldCircle() const;

  bool GetIsGhost() const;
  void SetIsGhost(bool isGhost);

  float GetDensity() const;
  float GetRestitution() const;
  float GetDynamicFriction() const;

  virtual void UpdateBoundingVolumes();

  // Internal ------------------------
  void SetNode(Physics2dNode* node);
  Physics2dNode* GetNode();

protected:
  friend PhysicsSpace2d;

  virtual Aabb2d GetLocalAabb() const;
  virtual Circle2d GetLocalCircle() const;
  void ComputeWorldAabb(const Matrix3& worldTransform2d, const Aabb2d& localAabb);
  void ComputeWorldCircle(const Matrix3& worldTransform2d, const Circle2d& localCircle);

  Collider2dType mColliderType = Collider2dType::None;

  PhysicsSpace2d* mSpace = nullptr;
  Zero::Link<Collider2d> mSpaceLink;
  Physics2dNode* mNode = nullptr;

  Aabb2d mWorldAabb;
  Circle2d mWorldCircle;

  HandleOf<Physics2dMaterial> mMaterial;
  bool mIsGhost = false;
};

}//namespace Physics2d
