#include "Precompiled.hpp"

#include "Physics2dStandard.hpp"

#include "Components/PhysicsSpace2d.hpp"
#include "Components/RigidBody2d.hpp"

#include "Components/Colliders/BoxCollider2d.hpp"
#include "Components/Colliders/CircleCollider2d.hpp"

#include "Components/CollisionDebug.hpp"
#include "Components/Physics2dDebugDrawConfig.hpp"
#include "Components/Physics2dNodeComponent.hpp"

#include "Resources/Physics2dMaterial.hpp"

namespace Zero
{

using namespace Physics2d;

//-------------------------------------------------------------------Physics2dLibrary
ZilchDefineStaticLibrary(Physics2dLibrary)
{
  builder.CreatableInScriptDefault = false;

  // Resources
  ZilchInitializeType(Physics2dMaterial);

  ZilchInitializeType(PhysicsSpace2d);
  ZilchInitializeType(RigidBody2d);
  ZilchInitializeType(Collider2d);
  ZilchInitializeType(BoxCollider2d);
  ZilchInitializeType(CircleCollider2d);
  ZilchInitializeType(CollisionDebug);
  ZilchInitializeType(Physics2dDebugDrawConfig);
  ZilchInitializeType(Physics2dNodeComponent);
}

void Physics2dLibrary::Initialize()
{
  BuildStaticLibrary();
  MetaDatabase::GetInstance()->AddNativeLibrary(GetLibrary());

  //Create the material manager.
  InitializeResourceManager(Physics2dMaterialManager);
}

void Physics2dLibrary::Shutdown()
{
  GetLibrary()->ClearComponents();
}

}//namespace Zero
