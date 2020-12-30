#include "Precompiled.hpp"

#include "Components/Physics2dNodeComponent.hpp"

#include "Engine/Space.hpp"
#include "Components/PhysicsSpace2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Physics2dNode
ZilchDefineType(Physics2dNodeComponent, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);
  ZeroBindDependency(Zero::Transform);

  type->AddAttribute(Zero::ObjectAttributes::cHidden);
}

void Physics2dNodeComponent::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

void Physics2dNodeComponent::Initialize(Zero::CogInitializer& initializer)
{
}

void Physics2dNodeComponent::ComponentAdded(Zilch::BoundType* typeId, Zero::Component* component)
{
}

void Physics2dNodeComponent::ComponentRemoved(Zilch::BoundType* typeId, Zero::Component* component)
{
}

void Physics2dNodeComponent::OnDestroy(uint flags)
{
}

}//namespace Physics2d
