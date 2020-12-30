#pragma once

#include "Physics2dStandard.hpp"

#include "Common/Containers/InList.hpp"
#include "Physics2dCore/SpatialPartitions/SpatialPartitionData.hpp"

namespace Physics2d
{

class Collider2d;
class RigidBody2d;
class Physics2dNodeManager;

//-------------------------------------------------------------------PhysicsPhysics2dNode2dNodeComponent
class Physics2dNode
{
public:
  void SetBody(RigidBody2d* body);
  void ClearBody();
  void SetCollider(Collider2d* collider);
  void ClearCollider();

  void QueueBroadphaseInsert();
  void QueueBroadphaseUpdate();
  void QueueBroadphaseRemoval();
  void QueueMassCalculation();

  bool mQueued = false;
  bool mRecomputeMass = false;
  bool mRecomputeTransform = false;
  bool mBroadphaseInsert = false;
  bool mBroadphaseUpdate = false;
  bool mBroadphaseRemove = false;

  Zero::Link<Physics2dNode> mOwnershipLink;
  Zero::Link<Physics2dNode> mQueueLink;
  using OwnedNodeList = Zero::InList<Physics2dNode, &Physics2dNode::mOwnershipLink>;
  using QueuedNodeList = Zero::InList<Physics2dNode, &Physics2dNode::mQueueLink>;

  RigidBody2d* mRigidBody2d = nullptr;
  Collider2d* mCollider2d = nullptr;
  Physics2dNodeManager* mManager = nullptr;

  SpatialPartitionKey mSpatialPartitionKey;
};

}//namespace Physics2d
