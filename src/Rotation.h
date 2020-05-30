//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_ROTATION_H
#define GIGAENGINE_ROTATION_H
#define GLM_FORCE_AVX2
#define GLM_FORCE_ALIGNED
#include "Engine/Component/Component.h"
#include "LocalToWorldMatrix.h"
#include <rttr/type>
struct Rotation : public Component
{
    SET_AS_COMPONENT(Rotation);
    float Get() const { return value_; }
    void Set(float value)
    {
      if(value != value_)
      {
        TagManager::AddTag<DirtyTransform>(GetEntity());
        value_ = value;
      }
    }
private:
    float value_ = 0;
};


#endif //GIGAENGINE_ROTATION_H
