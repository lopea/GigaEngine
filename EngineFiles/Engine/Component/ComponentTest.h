//
// Created by javier on 5/3/2020.
//

#ifndef GIGAENGINE_COMPONENTTEST_H
#define GIGAENGINE_COMPONENTTEST_H

#include "Component.h"

struct ComponentTest : public Component
{
    float value = 0;
    SET_AS_COMPONENT(ComponentTest)
};


#endif //GIGAENGINE_COMPONENTTEST_H
