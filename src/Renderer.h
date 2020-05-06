//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_RENDERER_H
#define GIGAENGINE_RENDERER_H


#include "Mesh.h"
#include "Shader.h"
#include "Engine/Component/Component.h"

struct Renderer : public Component
{
    Shader shader;
    Mesh mesh_;
    SET_AS_COMPONENT
};


#endif //GIGAENGINE_RENDERER_H
