#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"
#include "Physics2dCore/Constraints/Constraint2dVector.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------Jacobian2d
class Jacobian2d : public Constraint2dVector
{
public:
  using Constraint2dVector::Constraint2dVector;
};

}//namespace Physics2d
