#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <rttr/registration.h>
Transform::Transform(GameObject* parent)
: Component(parent), position_(0.0f), rotation_(0),
scale_(1),  matrix_(1.0f), isDirty_(false) {}

void Transform::Update() {}

Component* Transform::Clone(GameObject* parent)
{
  return ShallowCopy<Transform>(parent);
}

glm::vec2 Transform::GetPosition() const
{
  return position_;
}

void Transform::SetPosition(glm::vec2 position)
{
  position_ = position;
}

glm::vec2 Transform::GetScale() const
{
  return scale_;
}

void Transform::SetScale(glm::vec2 scale)
{
  scale_ = scale;
  isDirty_ = true;
}

float Transform::GetRotation() const
{
  return rotation_;
}

void Transform::SetRotation(float rotation)
{
  rotation_ = rotation;
  isDirty_ = true;
}

glm::mat4x4 Transform::GetMatrix()
{

  if (isDirty_)
  {
    using namespace glm;
    matrix_ = identity<mat4x4>();

    matrix_ = glm::scale(matrix_, vec3(scale_, 1));
    matrix_ = rotate(matrix_, radians(rotation_), vec3(0, 0, 1));
    matrix_ = translate(matrix_, vec3(position_, 1));
    isDirty_ = false;
  }
  return matrix_;
}

RTTR_REGISTRATION
{
  using namespace rttr;
  registration::class_<Transform>("Transform")
  .property("position", &Transform::GetPosition, &Transform::SetPosition)
  .property("rotation",&Transform::GetRotation, &Transform::SetRotation)
  .property("scale", &Transform::GetScale, &Transform::SetScale);
}
