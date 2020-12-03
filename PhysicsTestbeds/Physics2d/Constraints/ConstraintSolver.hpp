#pragma once

#include "Physics2dStandard.hpp"

#include "Constraints/Constraint.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ConstraintSolver
class ConstraintSolver
{
public:

  void Add(Constraint* constraint);
  void Solve(float dt);

  void SolveIteration(float dt);
  
  size_t mIterationCount = 10;
  Zero::InList<Constraint, &Constraint::mSolverLink> mConstraints;
};

}//namespace Physics2d
