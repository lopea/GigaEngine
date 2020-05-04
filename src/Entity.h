//
// Created by javier on 5/3/2020.
//

#ifndef GIGAENGINE_ENTITY_H
#define GIGAENGINE_ENTITY_H
#include "ComponentManager.h"
template<typename T>
T& Entity::GetComponent ()
{
    return ComponentManager::GetComponent<T>(*this);
}
template<typename T>
T &Entity::AddComponent ()
{
    rttr::type t = rttr::type::get<T>();
    auto it = std::find(types_.begin(),types_.end(), t);
    if(it != types_.end())
        return GetComponent<T>();

    //add type to the list
    types_.push_back(t);

    //add type to the list
    return ComponentManager::AddComponent<T>(*this);
}
#endif //GIGAENGINE_ENTITY_H
