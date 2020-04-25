#pragma once
#include <string>
#include <unordered_map>

#include "../MaterialProperty.h"

class Material
{
public:
  std::unordered_map<std::string, MaterialProperty> properties_;
};
