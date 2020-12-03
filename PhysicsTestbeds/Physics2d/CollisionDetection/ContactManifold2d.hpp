#pragma once

#include "Physics2dStandard.hpp"

#include "Physics2dCore/Manifold2d.hpp"
#include "Components/Colliders/Collider2dPair.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ContactManifold2d
class ContactManifold2d : public Manifold2d
{
public:
  Collider2dPair mPair;
};

}//namespace Physics2d
