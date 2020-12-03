#include "Precompiled.hpp"

#include "Resources/Physics2dMaterial.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Physics2dMaterial
ZilchDefineType(Physics2dMaterial, builder, type)
{
  ZeroBindSetup(Zero::SetupMode::DefaultSerialization);
  ZeroBindComponent();
  ZeroBindDocumented();
  ZeroBindDependency(Zero::Space);
  
  ZilchBindFieldProperty(mDensity)->ZeroSerialize(1.0f);
  ZilchBindFieldProperty(mRestitution)->ZeroSerialize(0.25f);
  ZilchBindFieldProperty(mDynamicFriction)->ZeroSerialize(0.25f);
}

void Physics2dMaterial::Serialize(Zero::Serializer& stream)
{
  SerializeNameDefault(mDensity, 1.0f);
  SerializeNameDefault(mRestitution, 0.25f);
  SerializeNameDefault(mDynamicFriction, 0.25f);
}

void Physics2dMaterial::ResourceModified()
{
  if(mModified == false)
    return;

  mModified = false;
  // If our values change then we need to let all collider's who are using this resource know
  // so they can re-compute any necessary values (currently only the density)
  Zero::ResourceEvent toSend;
  toSend.EventResource = this;
  DispatchEvent(Zero::Events::ResourceModified, &toSend);
}

Physics2dMaterial::Physics2dMaterialHandle Physics2dMaterial::CreateRuntime()
{
  return Physics2dMaterialManager::CreateRuntime();
}

Physics2dMaterial::ResourceHandle Physics2dMaterial::Clone()
{
  return RuntimeClone();
}

Physics2dMaterial::Physics2dMaterialHandle Physics2dMaterial::RuntimeClone()
{
  Physics2dMaterial* clone = Physics2dMaterialManager::CreateRuntime();
  CopyTo(clone);
  return clone;
}

void Physics2dMaterial::CopyTo(Physics2dMaterial* destination)
{
  destination->mDensity = mDensity;
  destination->mRestitution = mRestitution;
  destination->mDynamicFriction = mDynamicFriction;
}

void Physics2dMaterial::UpdateAndNotifyIfModified()
{
  if(mModified == false)
    return;

  mModified = false;
  // If our values change then we need to let all collider's who are using this resource know
  // so they can re-compute any necessary values (currently only the density)
  Zero::ResourceEvent toSend;
  toSend.EventResource = this;
  DispatchEvent(Zero::Events::ResourceModified, &toSend);
}

//---------------------------------------------------------- Physics2dMaterialManager
ImplementResourceManager(Physics2dMaterialManager, Physics2dMaterial);

Physics2dMaterialManager::Physics2dMaterialManager(Zilch::BoundType* resourceType)
  : Zero::ResourceManager(resourceType)
{
  AddLoader("Physics2dMaterial", new Zero::TextDataFileLoader<Physics2dMaterialManager>());
  mCategory = "Physics2d";
  mCanAddFile = true;
  mOpenFileFilters.PushBack(Zero::FileDialogFilter("*.Physics2dMaterial.data"));
  DefaultResourceName = "DefaultPhysics2dMaterial";
  mCanCreateNew = true;
  mCanDuplicate = true;
  mNoFallbackNeeded = true;
  mExtension = Zero::DataResourceExtension;
}

void Physics2dMaterialManager::UpdateAndNotifyModifiedResources()
{
  for(size_t i = 0; i < mModifiedResources.Size(); ++i)
  {
    Physics2dMaterial* material = mModifiedResources[i];
    if(material != nullptr)
      material->UpdateAndNotifyIfModified();
  }
  mModifiedResources.Clear();
}

}//namespace Physics2d
