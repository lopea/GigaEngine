//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_TRANSLATION_H
#define GIGAENGINE_TRANSLATION_H
#define GLM_FORCE_AVX2
#define GLM_FORCE_ALIGNED
#include "Engine/Component/Component.h"
#include <glm.hpp>

struct Translation : public Component
{
    glm::vec3 value = glm::vec3(0);
    SET_AS_COMPONENT
};

#endif //GIGAENGINE_TRANSLATION_H
