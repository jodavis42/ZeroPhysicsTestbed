#include "Precompiled.hpp"

#include "Manifold2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ManifoldPoint2d
void ManifoldPoint2d::Flip()
{
  Math::Swap(mPoint0, mPoint1);
  mNormal *= -1;
}

//-------------------------------------------------------------------Manifold2d
void Manifold2d::Flip()
{
  for(size_t i = 0; i < mPointCount; ++i)
    mPoints[i].Flip();
}

}//namespace Physics2d
