#pragma once

#include "Physics2dStandard.hpp"

#include "Components/Colliders/Collider2d.hpp"
#include "CollisionDetection/ContactManifold2d.hpp"

namespace Physics2d
{

class Box2d;
class Circle2d;
class Collider2d;
class BoxCollider2d;
class CircleCollider2d;

//-------------------------------------------------------------------CollisionLibrary
class CollisionLibrary
{
public:
  CollisionLibrary();

  void Setup();
  bool TestPair(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds) const;

private:
  static Box2d ToShape(const BoxCollider2d& boxCollider);
  static Circle2d ToShape(const CircleCollider2d& circleCollider);

  typedef bool (*CollisionFunction)(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds);
  static bool BoxBox(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds);
  static bool BoxCircle(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds);
  static bool CircleBox(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds);
  static bool CircleCircle(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds);

  template <typename Collider0Type, typename Collider1Type>
  static bool TestGeneric(Collider2d* collider0, Collider2d* collider1, Array<ContactManifold2d>& manifolds);

  CollisionFunction mCollisionTable[Collider2dType::Size][Collider2dType::Size]{};
};

}//namespace Physics2d
