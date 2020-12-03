#pragma once

#include "Physics2dStandard.hpp"

namespace Physics2d
{

class Collider2d;

//-------------------------------------------------------------------Collider2dPair
class Collider2dPair
{
public:
  Collider2dPair() {}
  Collider2dPair(Collider2d* collider0, Collider2d* collider1);

  Collider2d*& operator[](size_t index);
  Collider2d* operator[](size_t index) const;

  float GetRestitution() const;
  float GetDynamicFriction() const;
  
  Collider2d* mColliders[2]{};
};

}//namespace Physics2d
