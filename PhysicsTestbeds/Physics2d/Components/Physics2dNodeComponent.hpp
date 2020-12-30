#pragma once

#include "Physics2dStandard.hpp"

namespace Physics2d
{

class Collider2d;
class RigidBody2d;
class Physics2dNode;

//-------------------------------------------------------------------Physics2dNodeComponent
class Physics2dNodeComponent : public Zero::Component
{
public:
  ZilchDeclareType(Physics2dNodeComponent, Zilch::TypeCopyMode::ReferenceType);

  void Serialize(Zero::Serializer& stream) override;
  void Initialize(Zero::CogInitializer& initializer) override;
  void ComponentAdded(Zilch::BoundType* typeId, Zero::Component* component) override;
  void ComponentRemoved(Zilch::BoundType* typeId, Zero::Component* component) override;
  void OnDestroy(uint flags = 0) override;

  Physics2dNode* mNode = nullptr;
};

}//namespace Physics2d
