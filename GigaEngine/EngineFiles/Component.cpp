#include "Component.h"
#include <rttr/registration>


RTTR_REGISTRATION
{
  rttr::registration::class_<Component>("Component");
}

Component::Component(GameObject* object) : parent_(object) {}

GameObject* Component::GetParent() const
{
  return parent_;
}
