#include "Precompiled.hpp"

#include "PrimitiveGeometry2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------IntersectionType
const char* IntersectionType::Names[] = {"Coplanar", "Outside", "Inside", "Overlaps", "NotImplemented"};

IntersectionType::IntersectionType() : mType(Coplanar) {}

IntersectionType::IntersectionType(Type type) : mType(type) {}

IntersectionType::operator bool() const
{
  return mType != Outside;
}

//-------------------------------------------------------------------RayIntersectionType
const char* RayIntersectionType::Names[] = {"None", "StartsInside", "Intersection"};

RayIntersectionType::RayIntersectionType() : mType(None) {}

RayIntersectionType::RayIntersectionType(Type type) : mType(type) {}

RayIntersectionType::operator bool() const
{
  return mType != None;
}

}//namespace Physics2d
