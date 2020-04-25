#pragma once
#include <rttr/registration_friend>
#include <rttr/type>

class GameObject;

class Component
{
public:
  Component(GameObject* object);
  virtual void Update() = 0;
  virtual void Render() {}
  virtual Component* Clone(GameObject*) = 0;
  virtual void OnDestroy() = 0;
  virtual void OnCollision() {};
  GameObject* GetParent() const;

protected:
  template <typename T>
  static Component* ShallowCopy(GameObject* parent);
private:
  GameObject* parent_;
  RTTR_ENABLE()
  
};

template <typename T>
Component* Component::ShallowCopy(GameObject* parent)
{
  return static_cast<Component*>(new T(parent));
}

