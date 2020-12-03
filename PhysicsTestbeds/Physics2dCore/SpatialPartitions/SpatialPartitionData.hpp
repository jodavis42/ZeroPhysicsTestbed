#pragma once

#include "Physics2dCore/Shapes/Aabb2d.hpp"
#include "Physics2dCore/Shapes/Circle2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------SpatialPartitionKey
class SpatialPartitionKey
{
public:
  union
  {
    void* mVoidData;
    size_t mSizeTData;
  };
};

//-------------------------------------------------------------------SpatialPartitionData
template <typename UserDataType>
class SpatialPartitionData
{
public:
  UserDataType mUserData;
  Aabb2d mAabb;
  Circle2d mCircle;
};

//-------------------------------------------------------------------QueryResult
template <typename UserDataType>
class QueryResult
{
public:
  QueryResult() {}
  QueryResult(float time, const UserDataType& userData)
    : mTime(time)
    , mUserData(userData)
  {
  }

  float mTime = 0.0f;
  UserDataType mUserData{};
};

//-------------------------------------------------------------------SelfQueryResult
template <typename UserDataType>
class SelfQueryResult
{
public:
  SelfQueryResult() {}
  SelfQueryResult(const UserDataType& userData0, const UserDataType& userData1)
    : mUserData0(userData0)
    , mUserData1(userData1)
  {
  }

  UserDataType mUserData0 {};
  UserDataType mUserData1 {};
};

}//namespace Physics2d
