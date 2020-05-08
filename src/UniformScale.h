//
// Created by lopea on 5/8/20.
//

#ifndef GIGAENGINE_UNIFORMSCALE_H
#define GIGAENGINE_UNIFORMSCALE_H


#include "Engine/Component/Component.h"

struct UniformScale : public Component {
    float value = 1;
    SET_AS_COMPONENT
};


#endif //GIGAENGINE_UNIFORMSCALE_H
