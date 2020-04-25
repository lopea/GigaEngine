#pragma once
#include <boost/uuid/uuid.hpp>
#include <string>
#include "Component.h"
#include <rttr/type>

class GameObject
{
public:

  //default GameObject Constructor
  GameObject();
  GameObject(std::string& name);
  GameObject(const char* name);
  template<typename T>
  T* GetComponent() const;
  template<typename T>
  T* AddComponent();
  std::string GetName() const;
  boost::uuids::uuid GetUUID() const;
  
private:
  std::string name_;
  bool isActive_;
  boost::uuids::uuid uuid_;
  std::unordered_map<rttr::type, class Component*> components;
  RTTR_ENABLE()
};


template <typename T>
T* GameObject::GetComponent() const
{
  rttr::type t = rttr::type::get<T>();

  for (auto it = components.begin(); it != components.end(); ++it)
  {
    if (t == it->first)
    {
      return static_cast<T*>(it->second);
    }
  }
  return nullptr;
}

template <typename T>
T* GameObject::AddComponent()
{
  
  rttr::type t = rttr::type::get<T>();
#if _DEBUG
  if(!t.is_derived_from<Component>())
  {
    //TODO: add a message that class is incompatible
  }
#endif
  auto it = components.find(t);
  if (it == components.end())
  {
    T* newComponent = new T(this);
    components.insert_or_assign(t, static_cast<class Component*>(newComponent));
    return newComponent;
  }

  //TODO: Add message saying component already exists
  return static_cast<T*>(it->second);

}


typedef class GameObject* GameObjectPtr;
