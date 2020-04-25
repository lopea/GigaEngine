#pragma once
#include <glm/detail/type_mat4x4.hpp>
#include <glm/vec2.hpp>
#include <rttr/registration_friend>
#include "Component.h"

class Transform : public Component
{
public:
  Transform(GameObject* other);

  void Update() override;
  Component* Clone(GameObject* parent) override;
  void OnDestroy() override {};

  glm::vec2 GetPosition() const;
  void SetPosition(glm::vec2 position);

  glm::vec2 GetScale() const;
  void SetScale(glm::vec2 scale);

  float GetRotation() const;
  void SetRotation(float rotation);

  glm::mat4x4 GetMatrix();
private:
  RTTR_ENABLE()
  RTTR_REGISTRATION_FRIEND
  glm::vec2 position_;
  float rotation_;
  glm::vec2 scale_;
  glm::mat4x4 matrix_;
  bool isDirty_;
};
