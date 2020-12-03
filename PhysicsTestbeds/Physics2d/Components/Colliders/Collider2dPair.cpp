#include "Precompiled.hpp"

#include "Collider2dPair.hpp"

#include "Components/Colliders/Collider2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Collider2dPair
Collider2dPair::Collider2dPair(Collider2d* collider0, Collider2d* collider1)
{
  mColliders[0] = collider0;
  mColliders[1] = collider1;
}

Collider2d*& Collider2dPair::operator[](size_t index)
{
  return mColliders[index];
}

Collider2d* Collider2dPair::operator[](size_t index) const
{
  return mColliders[index];
}

float Collider2dPair::GetRestitution() const
{
  float restitution0 = mColliders[0]->GetRestitution();
  float restitution1 = mColliders[1]->GetRestitution();
  return Math::Min(restitution0, restitution1);
}

float Collider2dPair::GetDynamicFriction() const
{
  float friction0 = mColliders[0]->GetDynamicFriction();
  float friction1 = mColliders[1]->GetDynamicFriction();
  return Math::Sqrt(friction0 * friction1);
}

}//namespace Physics2d
