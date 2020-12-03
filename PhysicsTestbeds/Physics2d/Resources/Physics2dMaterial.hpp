#pragma once

#include "Physics2dStandard.hpp"

#include "Engine/Resource.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Physics2dMaterial
class Physics2dMaterial : public Zero::DataResource
{
public:
  using Physics2dMaterialHandle = Zilch::HandleOf<Physics2dMaterial>;
  using ResourceHandle = Zilch::HandleOf<Zero::Resource>;

  ZilchDeclareType(Physics2dMaterial, TypeCopyMode::ReferenceType);

  //-------------------------------------------------------------------Resource Interface
  void Serialize(Zero::Serializer& stream) override;
  void ResourceModified() override;

  /// Creates a PhysicsMaterial for run-time modifications.
  static Physics2dMaterialHandle CreateRuntime();
  ResourceHandle Clone() override;
  /// Creates a clone of this material for run-time modifications.
  Physics2dMaterialHandle RuntimeClone();

  void CopyTo(Physics2dMaterial* destination);
  /// After modifying this resource, notify anyone using it to update
  /// now instead of at the next physics update.
  void UpdateAndNotifyIfModified();

  //-------------------------------------------------------------------Properties
  float mDensity = 1.0f;
  float mRestitution = 0.25f;
  float mDynamicFriction = 0.25f;
  bool mModified = false;
};

//---------------------------------------------------------- Physics2dMaterialManager
class Physics2dMaterialManager : public Zero::ResourceManager
{
public:
  DeclareResourceManager(Physics2dMaterialManager, Physics2dMaterial);
  Physics2dMaterialManager(Zilch::BoundType* resourceType);

  void UpdateAndNotifyModifiedResources();

  using Physics2dMaterialHandle = Physics2dMaterial::Physics2dMaterialHandle;
  Array<Physics2dMaterialHandle> mModifiedResources;
};

}//namespace Physics2d
