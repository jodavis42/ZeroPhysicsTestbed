#include "Precompiled.hpp"

#include "Components/Physics2dDebugDrawConfig.hpp"

#include "Engine/Cog.hpp"
#include "Engine/DebugDraw.hpp"
#include "Geometry/DebugDraw.hpp"
#include "Common/Math/ByteColor.hpp"

#include "Components/PhysicsSpace2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Physics2dDebugDrawConfig
ZilchDefineType(Physics2dDebugDrawConfig, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Space);
  
  ZilchBindFieldProperty(mDrawColliderAabbs)->ZeroSerialize(true);
  ZilchBindFieldProperty(mColliderAabbColor)->ZeroSerialize(ToFloatColor(Color::Gray));\
  ZilchBindFieldProperty(mDrawColliderCircles)->ZeroSerialize(true);
  ZilchBindFieldProperty(mColliderCircleColor)->ZeroSerialize(ToFloatColor(Color::Gray));
}

void Physics2dDebugDrawConfig::Serialize(Zero::Serializer& stream)
{
  MetaSerializeProperties(this, stream);
}

Physics2dDebugDrawConfig* Physics2dDebugDrawConfig::GetConfig(const PhysicsSpace2d* space)
{
  if(space != nullptr)
    return space->GetOwner()->has(Physics2dDebugDrawConfig);
  return nullptr;
}

}//namespace Physics2d
