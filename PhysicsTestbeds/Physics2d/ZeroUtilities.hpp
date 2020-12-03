#pragma once

#include "Physics2dStandard.hpp"

namespace Zero
{
class Transform;
}

namespace Physics2d
{

//-------------------------------------------------------------------ZeroUtilities
class ZeroUtilities
{
public:
  static Vector2 GetWorldScale(Zero::Transform* transform);
  static void SetWorldScale(Zero::Transform* transform, const Vector2& worldScale);

  static float GetWorldRotation(Zero::Transform* transform);
  static void SetWorldRotation(Zero::Transform* transform, float worldRotation);

  static Vector2 GetWorldTranslation(Zero::Transform* transform);
  static void SetWorldTranslation(Zero::Transform* transform, const Vector2& worldTranslation);

  static void ToWorldTransform2d(Zero::Transform* transform, Vector2& worldScale, float& worldRotation, Vector2& worldTranslation);
  static Matrix3 ToWorldTransform2d(Zero::Transform* transform);

  static float ToRotation2d(const Matrix3& rotation);
  static Matrix2 ToMatrix2(const Matrix3& rotation);
  static Matrix3 ToMatrix3(float rotation);
  static Matrix3 ToMatrix3(const Matrix2& rotation);
  static Quaternion ToQuaternion(float rotation);
  static Quaternion ToQuaternion(const Matrix2& rotation);
};

}//namespace Physics2d
