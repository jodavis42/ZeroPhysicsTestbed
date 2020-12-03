#include "Precompiled.hpp"

#include "ConstraintSolver.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ConstraintSolver
void ConstraintSolver::Add(Constraint* constraint)
{
  mConstraints.PushBack(constraint);
}

void ConstraintSolver::Solve(float dt)
{
  for(size_t i = 0; i < mIterationCount; ++i)
    SolveIteration(dt);
}

void ConstraintSolver::SolveIteration(float dt)
{
  for(auto range = mConstraints.All(); !range.Empty(); range.PopFront())
  {
    Constraint& constraint = range.Front();
    constraint.Solve(dt);
  }
}

}//namespace Physics2d
