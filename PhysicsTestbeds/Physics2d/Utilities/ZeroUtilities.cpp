#include "Precompiled.hpp"

#include "ZeroUtilities.hpp"

#include "Engine/Transform.hpp"

namespace Physics2d
{

//-------------------------------------------------------------------ZeroUtilities
Vector2 ZeroUtilities::GetWorldScale(Zero::Transform* transform)
{
  return Math::ToVector2(transform->GetWorldScale());
}

void ZeroUtilities::SetWorldScale(Zero::Transform* transform, const Vector2& worldScale)
{
  Vector3 worldScale3d = Math::ToVector3(worldScale, 0.0f);
  transform->SetWorldScaleInternal(worldScale3d);
}

float ZeroUtilities::GetWorldRotation(Zero::Transform* transform)
{
  Math::Quaternion rotationQuat = transform->GetWorldRotation();
  Math::EulerAngles eulerAngles = Math::ToEulerAngles(rotationQuat);
  return eulerAngles[2];
}

void ZeroUtilities::SetWorldRotation(Zero::Transform* transform, float worldRotation)
{
  Math::Quaternion worldRotation3d = ToQuaternion(worldRotation);
  transform->SetWorldRotationInternal(worldRotation3d);
}

Vector2 ZeroUtilities::GetWorldTranslation(Zero::Transform* transform)
{
  return Math::ToVector2(transform->GetWorldTranslation());
}

void ZeroUtilities::SetWorldTranslation(Zero::Transform* transform, const Vector2& worldTranslation)
{
  Vector3 worldTranslation3d = Math::ToVector3(worldTranslation, 0.0f);
  transform->SetWorldTranslationInternal(worldTranslation3d);
}

void ZeroUtilities::ToWorldTransform2d(Zero::Transform* transform, Vector2& worldScale, float& worldRotation, Vector2& worldTranslation)
{
  Matrix4 worldMatrix3d = transform->GetWorldMatrix();
  Vector3 worldScale3d, worldTranslation3d;
  Matrix3 worldRotation3d;
  worldMatrix3d.Decompose(&worldScale3d, &worldRotation3d, &worldTranslation3d);
  worldScale = Math::ToVector2(worldScale3d);
  worldRotation = ToRotation2d(worldRotation3d);
  worldTranslation = Math::ToVector2(worldTranslation3d);
}

Matrix3 ZeroUtilities::ToWorldTransform2d(Zero::Transform* transform)
{
  Vector2 worldScale, worldTranslation;
  float worldRotation;
  ZeroUtilities::ToWorldTransform2d(transform, worldScale, worldRotation, worldTranslation);
  return Matrix3::GenerateTransform(worldTranslation, worldRotation, worldScale);
}

float ZeroUtilities::ToRotation2d(const Matrix3& rotation)
{
  Math::EulerAngles eulerAngles = Math::ToEulerAngles(rotation);
  return eulerAngles[2];
}

Matrix2 ZeroUtilities::ToMatrix2(const Matrix3& rotation)
{
  Matrix2 result;
  result.m00 = rotation.m00;
  result.m01 = rotation.m01;
  result.m10 = rotation.m10;
  result.m11 = rotation.m11;
  return result;
}

Matrix3 ZeroUtilities::ToMatrix3(float rotation)
{
  return Matrix3::GenerateRotation(rotation);
}

Matrix3 ZeroUtilities::ToMatrix3(const Matrix2& rotation)
{
  return Matrix3::GenerateRotation(rotation);
}

Quaternion ZeroUtilities::ToQuaternion(float rotation)
{
  return Math::ToQuaternion(Math::Vector3(0, 0, 1), rotation);
}

Quaternion ZeroUtilities::ToQuaternion(const Matrix2& rotation)
{
  Matrix3 mat3 = ToMatrix3(rotation);
  return Math::ToQuaternion(mat3);
}

}//namespace Physics2d
