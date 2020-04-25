#pragma once
#include <glm/vec2.hpp>
#include <rttr/registration_friend.h>


#include "Component.h"

class Movement : public Component
{
public:
  Movement(GameObject* parent);
  glm::vec2& GetVelocity();
  float& GetAcceleration();
  void Update() override {}
  Component* Clone(GameObject* other) override;
  void OnDestroy() override {}
private:
  glm::vec2 velocity_;
  float acceleration_;
  RTTR_ENABLE(Component)
  RTTR_REGISTRATION_FRIEND
};
