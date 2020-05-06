//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_ROTATION_H
#define GIGAENGINE_ROTATION_H

#include "Engine/Component/Component.h"
#include <rttr/type>
struct Rotation : public Component
{
    float value = 0;
    SET_AS_COMPONENT
};


#endif //GIGAENGINE_ROTATION_H
