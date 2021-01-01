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
    SelfQueryRange(SelfType* self)
    {
      mSelf = self;
      // Find the first valid index then increment them both until a valid pair is found.
      SkipEmptyIndices(mIndex0);
      mIndex1 = mIndex0 + 1;
      SkipEmptyIndices();
    }

    bool Empty() const
    {
      size_t size = mSelf->mSlots.Size();
      return mIndex0 >= size || mIndex1 >= size;
    }

    void PopFront()
    {
      ++mIndex1;
      SkipEmptyIndices();
    }

    SelfQueryResultType Front()
    {
      return SelfQueryResultType(mSelf->GetDataAt(mIndex0), mSelf->GetDataAt(mIndex1));
    }

  private:
    
    void SkipEmptyIndices()
    {
      if(!SkipEmptyIndices(mIndex1))
      {
        // If we reached the end of the list then advance the index0 instead. If we can't advance the index0 we're done.
        ++mIndex0;
        if(!SkipEmptyIndices(mIndex0))
        {
          mIndex1 = mIndex0 = mSelf->mSlots.Size();
          return;
        }

        // Now update index1
        mIndex1 = mIndex0 + 1;
      }
    }

    bool SkipEmptyIndices(size_t& index)
    {
      while(index < mSelf->mSlots.Size())
      {
        if(!mSelf->mSlots[index].mIsEmpty)
          return true;

        ++index;
      }
      return false;
    }

    friend SelfType;
    SelfType* mSelf = nullptr;
    size_t mIndex0 = 0;
    size_t mIndex1 = 1;
  };

  SelfQueryRange SelfQuery()
  {
    SelfQueryRange range(this);
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
