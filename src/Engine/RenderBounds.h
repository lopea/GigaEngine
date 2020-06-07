//
// Created by lopea on 6/4/20.
//

#ifndef GIGAENGINE_RENDERBOUNDS_H
#define GIGAENGINE_RENDERBOUNDS_H

#include "Component/Component.h"

struct RenderBounds : public Component
{
    SET_AS_COMPONENT(RenderBounds)
  float width = 1;
  float height = 1;
};

#endif //GIGAENGINE_RENDERBOUNDS_H
