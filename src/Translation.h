//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_TRANSLATION_H
#define GIGAENGINE_TRANSLATION_H
#define GLM_FORCE_AVX2
#define GLM_FORCE_ALIGNED
#include "Engine/Component/Component.h"
#include "LocalToWorldMatrix.h"
#include "Engine/Tag/TagManager.h"
#include <glm.hpp>

struct Translation : public Component
{
    SET_AS_COMPONENT(Translation)
    glm::vec3 Get() const
    {
      return value_;
    }

    void Set(glm::vec3 value)
    {
      if(value != value_)
      {
        TagManager::AddTag<DirtyTransform>(GetEntity());
        value_ = value;
      }
    }
private:
    glm::vec3 value_ = glm::vec3(0);
};

#endif //GIGAENGINE_TRANSLATION_H
