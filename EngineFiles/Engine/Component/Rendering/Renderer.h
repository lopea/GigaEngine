//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_RENDERER_H
#define GIGAENGINE_RENDERER_H


#include "Mesh.h"
#include "Shader.h"
#include "../Component.h"

struct Renderer : public Component
{
    SET_AS_COMPONENT(Renderer)
    Shader shader;
    Mesh mesh_;
};


#endif //GIGAENGINE_RENDERER_H
