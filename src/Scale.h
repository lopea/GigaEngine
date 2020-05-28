//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_SCALE_H
#define GIGAENGINE_SCALE_H
#define GLM_FORCE_AVX2
#define GLM_FORCE_ALIGNED
#include "Engine/Component/Component.h"
#include "LocalToWorldMatrix.h"
#include <glm.hpp>
struct Scale : public Component
{
    SET_AS_COMPONENT(Scale)
    glm::vec3 Get() const
    {
      return value_;
    }

    void Set(glm::vec3 &value)
    {
      if(value != value_)
      {
        ComponentManager::AddComponent<DirtyTransform>(GetEntity());
        value_ = value;
      }
    }
private:
    glm::vec3 value_ = glm::vec3(0);
};


#endif //GIGAENGINE_SCALE_H
