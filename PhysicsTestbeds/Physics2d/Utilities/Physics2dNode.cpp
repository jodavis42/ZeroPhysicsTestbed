#include "Precompiled.hpp"

#include "Utilities/Physics2dNode.hpp"

#include "Engine/Space.hpp"
#include "Components/PhysicsSpace2d.hpp"
#include "Components/Colliders/Collider2d.hpp"
#include "Components/RigidBody2d.hpp"
#include "Utilities/Physics2dNodeManager.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Physics2dNode
void Physics2dNode::SetBody(RigidBody2d* body)
{
  mRigidBody2d = body;
  mRigidBody2d->SetNode(this);
}

void Physics2dNode::ClearBody()
{
  if(mRigidBody2d != nullptr)
    mRigidBody2d->SetNode(nullptr);
  mRigidBody2d = nullptr;
}

void Physics2dNode::SetCollider(Collider2d* collider)
{
  mCollider2d = collider;
  mCollider2d->SetNode(this);
}

void Physics2dNode::ClearCollider()
{
  if(mCollider2d != nullptr)
    mCollider2d->SetNode(nullptr);
  mCollider2d = nullptr;
}

void Physics2dNode::QueueBroadphaseInsert()
{
  mManager->TryQueue(this);
  mBroadphaseInsert = true;
  // If there was a removal queued, then insert + remove = do nothing
  if(mBroadphaseRemove == true)
  {
    mBroadphaseRemove = false;
    mBroadphaseInsert = false;
    mBroadphaseUpdate = true;
  }
}

void Physics2dNode::QueueBroadphaseUpdate()
{
  mManager->TryQueue(this);
  
  // Don't queue updates if a removal is queued
  if(mBroadphaseRemove == true)
    mBroadphaseUpdate = false;
  else
    mBroadphaseUpdate = true;
}

void Physics2dNode::QueueBroadphaseRemoval()
{
  mManager->TryQueue(this);
  mBroadphaseRemove = true;
  // If there was an insert queued, then insert + remove = do nothing
  if(mBroadphaseInsert == true)
  {
    mBroadphaseRemove = false;
    mBroadphaseInsert = false;
    mBroadphaseUpdate = false;
  }
  // Otherwise remove any queued update since we're removing
  else
    mBroadphaseUpdate = false;
}

void Physics2dNode::QueueMassCalculation()
{
  mRecomputeMass = true;
  mManager->TryQueue(this);
}

}//namespace Physics2d
