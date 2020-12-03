#include "Precompiled.hpp"

#include "Constraint.hpp"

#include "Engine/Cog.hpp"
#include "Engine/Space.hpp"

#include "Components/RigidBody2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Constraint
ZilchDefineType(Constraint, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Cog);

  ZilchBindFieldProperty(mActive)->ZeroSerialize(true);
}

void Constraint::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

}//namespace Physics2d
