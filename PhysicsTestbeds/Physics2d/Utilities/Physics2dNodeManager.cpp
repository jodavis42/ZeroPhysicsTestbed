#include "Precompiled.hpp"

#include "Physics2dNodeManager.hpp"

#include "Components/Physics2dNodeComponent.hpp"
#include "Components/PhysicsSpace2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Physics2dNodeManager
Physics2dNodeManager::~Physics2dNodeManager()
{
  mQueuedNodes.Clear();
  DeleteQueue(mOwnedNodes);
}

Physics2dNode* Physics2dNodeManager::GetNode(Zero::Cog* cog) const
{
  Physics2dNodeComponent* nodeComponent = cog->has(Physics2dNodeComponent);
  if(nodeComponent == nullptr)
    return nullptr;

  return nodeComponent->mNode;
}

Physics2dNode* Physics2dNodeManager::GetOrCreateNode(Zero::Cog* cog)
{
  Physics2dNodeComponent* nodeComponent = Zero::HasOrAdd<Physics2dNodeComponent>(cog);
  if(nodeComponent->mNode == nullptr)
  {
    nodeComponent->mNode = new Physics2dNode();
    mOwnedNodes.PushBack(nodeComponent->mNode);
  }
  nodeComponent->mNode->mManager = this;
  return nodeComponent->mNode;
}

bool Physics2dNodeManager::TryQueue(Physics2dNode* node)
{
  if(node->mQueued)
    return false;

  node->mQueued = true;
  mQueuedNodes.PushBack(node);
  return true;
}

bool Physics2dNodeManager::TryDequeue(Physics2dNode* node)
{
  if(!node->mQueued)
    return false;

  mQueuedNodes.Erase(node);
  node->mQueued = false;
  return true;
}

void Physics2dNodeManager::ProcessQueue(PhysicsSpace2d* space)
{
  for(auto range = mQueuedNodes.All(); !range.Empty(); range.PopFront())
  {
    Physics2dNode& node = range.Front();

    if(node.mBroadphaseRemove)
    {
      space->mSpatialPartition.Remove(node.mSpatialPartitionKey);
      node.mBroadphaseRemove = false;
    }
    if(node.mBroadphaseInsert)
    {
      SpatialPartitionData<Collider2d*> data;
      space->ToSpatialPartitionData(node.mCollider2d, data);
      node.mSpatialPartitionKey = space->mSpatialPartition.Insert(data);
      node.mBroadphaseInsert = false;
    }
    if(node.mBroadphaseUpdate)
    {
      SpatialPartitionData<Collider2d*> data;
      space->ToSpatialPartitionData(node.mCollider2d, data);
      space->mSpatialPartition.Update(node.mSpatialPartitionKey, data);
      node.mBroadphaseUpdate = false;
    }
    if(node.mRecomputeMass)
    {
      Collider2dMassData massData;
      if(node.mCollider2d != nullptr)
        massData = node.mCollider2d->ComputeMassData();
      if(node.mRigidBody2d != nullptr)
      {
        float invMass = 1.0f / massData.mWorldMass;
        float invInertia = 1.0f / massData.mWorldInertia;
        if(node.mRigidBody2d->GetIsStatic())
        {
          invMass = invInertia = 0.0f;
        }

        node.mRigidBody2d->SetInvMass(invMass);
        node.mRigidBody2d->SetInvInertia(invInertia);
      }
      // To Do
    }
    node.mQueued = false;
  }
  mQueuedNodes.Clear();
}

void Physics2dNodeManager::DeleteQueue(OwnedNodeList& nodeList)
{
  while(!nodeList.Empty())
  {
    Physics2dNode* node = &nodeList.Front();
    nodeList.PopFront();
    delete node;
  }
}

}//namespace Physics2d
