#include "Precompiled.hpp"

#include "Integrators2d.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------EulerIntegrator
void EulerIntegrator::IntegrateLinearVelocity(Vector2& linearVelocity, const Vector2& force, float invMass, float dt)
{
  linearVelocity += force * invMass * dt;
}

void EulerIntegrator::IntegrateAngularVelocity(float& angularVelocity, float torque, float invInertia, float dt)
{
  angularVelocity += torque * invInertia * dt;
}

void EulerIntegrator::IntegratePosition(Vector2& position, const Vector2& linearVelocity, float dt)
{
  position += linearVelocity * dt;
}

void EulerIntegrator::IntegrateRotation(float& rotation, float angularVelocity, float dt)
{
  rotation += angularVelocity * dt;
}

}//namespace Physics2d
