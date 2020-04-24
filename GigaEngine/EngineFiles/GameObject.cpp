#include "GameObject.h"
#include "boost/uuid/random_generator.hpp"
#include <rttr/registration>
GameObject::GameObject() : name_("New GameObject"), uuid_(boost::uuids::random_generator()())
{
  
}

GameObject::GameObject(std::string& name) : name_(name), uuid_(boost::uuids::random_generator()()) { }

GameObject::GameObject(const char* name): name_(name), uuid_(boost::uuids::random_generator()()) { }

RTTR_REGISTRATION
{
  using namespace rttr;
  registration::class_<GameObject>("GameObject");
}
}