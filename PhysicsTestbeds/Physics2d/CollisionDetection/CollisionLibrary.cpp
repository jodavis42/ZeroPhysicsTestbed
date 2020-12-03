#include "Precompiled.hpp"

#include "CollisionLibrary.hpp"

#include "Components/Colliders/BoxCollider2d.hpp"
#include "Components/Colliders/CircleCollider2d.hpp"
#include "Shapes/Circle2d.hpp"
#include "Shapes/Box2d.hpp"

#include "Physics2dCore/SimpleIntersection.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------CollisionLibrary
CollisionLibrary::CollisionLibrary()
{
  Setup();
}

void CollisionLibrary::Setup()
{
  mCollisionTable[(size_t)Collider2dType::Box][(size_t)Collider2dType::Box] = &BoxBox;
  mCollisionTable[(size_t)Collider2dType::Box][(size_t)Collider2dType::Circle] = &BoxCircle;
  mCollisionTable[(size_t)Collider2dType::Circle][(size_t)Collider2dType::Box] = &CircleBox;
  mCollisionTable[(size_t)Collider2dType::Circle][(size_t)Collider2dType::Circle] = &CircleCircle;
}

bool CollisionLibrary::TestPair(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds) const
{
  Collider2dType type0 = collider0->GetType();
  Collider2dType type1 = collider1->GetType();
  CollisionFunction fn = mCollisionTable[(size_t)type0][(size_t)type1];
  if(fn != nullptr)
    return (*fn)(collider0, collider1, manifolds);
  return false;
}

Box2d CollisionLibrary::ToShape(const BoxCollider2d& boxCollider)
{
  return boxCollider.ToShape();
}

Circle2d CollisionLibrary::ToShape(const CircleCollider2d& circleCollider)
{
  return circleCollider.ToShape();
}

bool CollisionLibrary::BoxBox(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds)
{
  return TestGeneric<BoxCollider2d, BoxCollider2d>(collider0, collider1, manifolds);
}

bool CollisionLibrary::BoxCircle(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds)
{
  return TestGeneric<BoxCollider2d, CircleCollider2d>(collider0, collider1, manifolds);
}

bool CollisionLibrary::CircleBox(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds)
{
  return BoxCircle(collider1, collider0, manifolds);
}

bool CollisionLibrary::CircleCircle(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds)
{
  return TestGeneric<CircleCollider2d, CircleCollider2d>(collider0, collider1, manifolds);
}

template <typename Collider0Type, typename Collider1Type>
bool CollisionLibrary::TestGeneric(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds)
{
  // Convert the colliders to their shapes
  Collider0Type* typedCollider0 = static_cast<Collider0Type*>(collider0);
  Collider1Type* typedCollider1 = static_cast<Collider1Type*>(collider1);
  auto shape0 = ToShape(*typedCollider0);
  auto shape1 = ToShape(*typedCollider1);

  // Test the shapes for intersection
  ContactManifold2d manifold;
  if(!SimpleIntersection::TestIntersection(shape0, shape1, manifold))
    return false;
  
  manifold.mPair = Collider2dPair(collider0, collider1);
  manifolds.PushBack(manifold);
  return true;
}

}//namespace Physics2d
