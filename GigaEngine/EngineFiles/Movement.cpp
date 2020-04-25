#include "Movement.h"

#include <rttr/registration>

Movement::Movement(GameObject* parent) : Component(parent), velocity_(0, 0), acceleration_(0){}

glm::vec2& Movement::GetVelocity()
{
  return velocity_;
}

float& Movement::GetAcceleration()
{
  return acceleration_;
}

Component* Movement::Clone(GameObject* other)
{
  return ShallowCopy<Movement>(other);
}

RTTR_REGISTRATION
{
  using namespace rttr;
  registration::class_<Movement>("Movement");
}
