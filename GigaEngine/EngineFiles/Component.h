#pragma once
#include "GameObject.h"
#include "rttr/type"
#include "rttr/registration_friend"

class GameObject;
typedef GameObject* GameObjectPtr;
class Component
{
public:
  Component(GameObject* object);
  virtual void Update() = 0;
  virtual void Render() {}
  virtual void Clone() = 0;
  virtual void OnDestroy() = 0;
  virtual void OnCollision() {};
  GameObjectPtr GetParent() const;
private:
  GameObjectPtr parent_;
  RTTR_ENABLE()

};

