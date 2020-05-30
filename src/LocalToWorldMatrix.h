//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_LOCALTOWORLDMATRIX_H
#define GIGAENGINE_LOCALTOWORLDMATRIX_H
#define GLM_FORCE_AVX2
#define GLM_FORCE_ALIGNED
#include <glm.hpp>
#include <ext.hpp>
#include "Engine/Component/Component.h"
#include "Engine/Tag/TagBase.h"

struct LocalToWorldMatrix : public Component
{
    glm::mat4x4 value = glm::identity<glm::mat4x4>();
    SET_AS_COMPONENT(LocalToWorldMatrix)
};

struct DirtyTransform : public TagBase {SET_AS_TAG()};


#endif //GIGAENGINE_LOCALTOWORLDMATRIX_H
