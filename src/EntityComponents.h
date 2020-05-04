//
// Created by javier on 5/3/2020.
//

#ifndef GIGAENGINE_ENTITYCOMPONENTS_H
#define GIGAENGINE_ENTITYCOMPONENTS_H
#include "ComponentManager.h"
template<typename T>
bool Entity::GetComponent (T &&result)
{
    return ComponentManager::GetComponent<T>(*this, result);
}
template<typename T>
T &Entity::AddComponent ()
{

    return ComponentManager::AddComponent<T>(*this);
}
#endif //GIGAENGINE_ENTITYCOMPONENTS_H
