#pragma once

#include "Physics2dCore/SpatialPartitions/SpatialPartitionData.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------SimpleIntersection
template <typename UserDataType>
class NSquaredSpatialPartition
{
public:
  using SelfType = NSquaredSpatialPartition<UserDataType>;
  using DataType = SpatialPartitionData<UserDataType>;
  using SelfQueryResultType = SelfQueryResult<UserDataType>;
  
  SpatialPartitionKey Insert(DataType& data)
  {
    SpatialPartitionKey key;
    key.mSizeTData = FindFreeIndexOrResize();
    ItemSlot& itemSlot = mSlots[key.mSizeTData];
    itemSlot.mUserData = data.mUserData;
    itemSlot.mIsEmpty = false;
    return key;
  }

  void Update(SpatialPartitionKey& key, DataType& data)
  {
    ItemSlot& itemSlot = mSlots[key.mSizeTData];
    itemSlot.mUserData = data.mUserData;
  }

  void Remove(SpatialPartitionKey& key)
  {
    ItemSlot& itemSlot = mSlots[key.mSizeTData];
    itemSlot.mIsEmpty = true;
    mFreeIndices.PushBack(key.mSizeTData);
  }


  class SelfQueryRange
  {
  public:
    bool Empty() const
    {
      return mIndex0 >= mSelf->mSlots.Size();
    }

    void PopFront()
    {
      ++mIndex1;
      while(mIndex1 >= mSelf->mSlots.Size())
      {
        ++mIndex0;
        if(Empty())
          break;
        mIndex1 = mIndex0 + 1;
      }
    }

    SelfQueryResultType Front()
    {
      return SelfQueryResultType(mSelf->GetDataAt(mIndex0), mSelf->GetDataAt(mIndex1));
    }

  private:
    friend SelfType;
    SelfType* mSelf = nullptr;
    size_t mIndex0 = 0;
    size_t mIndex1 = 1;
  };

  SelfQueryRange SelfQuery()
  {
    SelfQueryRange range;
    range.mSelf = this;
    return range;
  }

private:

  UserDataType& GetDataAt(size_t index)
  {
    return mSlots[index].mUserData;
  }
  
  size_t FindFreeIndexOrResize()
  {
    if(!mFreeIndices.Empty())
    {
      size_t index = mFreeIndices.Back();
      mFreeIndices.PopBack();
      return index;
    }
    size_t index = mSlots.Size();
    mSlots.Resize(mSlots.Size() + 1);
    return index;
  }

  struct ItemSlot
  {
    UserDataType mUserData;
    bool mIsEmpty = true;
  };
  Zero::Array<ItemSlot> mSlots;
  Zero::Array<size_t> mFreeIndices;
};

}//namespace Physics2d
