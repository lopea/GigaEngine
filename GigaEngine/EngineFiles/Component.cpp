#include "Component.h"
#include "rttr/registration"


RTTR_REGISTRATION
{
  rttr::registration::class_<Component>("Component");
}

GameObjectPtr Component::GetParent() const
{
  return parent_;
}
