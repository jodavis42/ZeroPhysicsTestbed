#pragma once

#include "Physics2dStandard.hpp"

#include "Common/Containers/InList.hpp"
#include "Utilities/Physics2dNode.hpp"

namespace Physics2d
{

class PhysicsSpace2d;

//-------------------------------------------------------------------Physics2dNodeManager
class Physics2dNodeManager
{
public:
  using OwnedNodeList = Physics2dNode::OwnedNodeList;
  using QueuedNodeList = Physics2dNode::QueuedNodeList;

  ~Physics2dNodeManager();

  Physics2dNode* GetNode(Zero::Cog* cog) const;
  Physics2dNode* GetOrCreateNode(Zero::Cog* cog);

  bool TryQueue(Physics2dNode* node);
  bool TryDequeue(Physics2dNode* node);

  void ProcessQueue(PhysicsSpace2d* space);

  static void DeleteQueue(OwnedNodeList& nodeList);
  
  OwnedNodeList mOwnedNodes;
  QueuedNodeList mQueuedNodes;
};

}//namespace Physics2d
