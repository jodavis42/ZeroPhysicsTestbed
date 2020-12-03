#pragma once

#include "Physics2dCore/Physics2dCoreStandard.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------EulerIntegrator
class EulerIntegrator
{
public:
  static void IntegrateLinearVelocity(Vector2& linearVelocity, const Vector2& force, float invMass, float dt);
  static void IntegrateAngularVelocity(float& angularVelocity, float torque, float invInertia, float dt);
  static void IntegratePosition(Vector2& position, const Vector2& linearVelocity, float dt);
  static void IntegrateRotation(float& rotation, float angularVelocity, float dt);
};

}//namespace Physics2d
