#include "GameObject.h"
#include "boost/uuid/random_generator.hpp"
#include <rttr/registration>
GameObject::GameObject() : name_("New GameObject"), isActive_(true), uuid_(boost::uuids::random_generator()()) { }

GameObject::GameObject(std::string& name) : name_(name), isActive_(true), uuid_(boost::uuids::random_generator()()) { }

GameObject::GameObject(const char* name): name_(name), isActive_(true), uuid_(boost::uuids::random_generator()()) { }

 boost::uuids::uuid GameObject::GetUUID() const
{
  return uuid_;
}

std::string GameObject::GetName() const
{
  return name_;
}


RTTR_REGISTRATION
{
  //just registering the GameObject to the rttr database
  using namespace rttr;
  registration::class_<GameObject>("GameObject");
}
