//
// Created by lopea on 5/8/20.
//

#ifndef GIGAENGINE_UNIFORMSCALE_H
#define GIGAENGINE_UNIFORMSCALE_H


#include "Engine/Component/Component.h"

struct UniformScale : public Component
{
    SET_AS_COMPONENT(UniformScale)
    float Get() const { return value_; }
    void Set(float value)
    {
      if(value != value_)
      {
        ComponentManager::AddComponent<DirtyTransform>(GetEntity());
        value_ = value;
      }
    }
private:
    float value_ = 1;
};


#endif //GIGAENGINE_UNIFORMSCALE_H
