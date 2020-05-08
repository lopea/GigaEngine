//
// Created by javier on 5/3/2020.
//

#ifndef GIGAENGINE_ENTITY_H
#define GIGAENGINE_ENTITY_H
#include "EntityBase.h"
#include "../Component/ComponentExceptions.h"
#include "../Component/ComponentManager.h"
#include <rttr/type>

template<typename T>
T& Entity::GetComponent ()
{
    auto it = components_.find(rttr::type::get<T>().get_id());

    if(it != components_.end())
        return *static_cast<T*>(it->second);

    throw ComponentNotFoundExeption(rttr::type::get<T>());
    //return ComponentManager::GetComponent<T>(*this);
}

template<typename T>
T &Entity::AddComponent ()
{
    rttr::type t = rttr::type::get<T>();

    T& res = ComponentManager::AddComponent<T>(*this);

    //add type to the list
    components_.insert(std::pair<rttr::type::type_id, Component*>(t.get_id(), &res));

    //add type to the list
    return *static_cast<T*>(&res);
}

template<typename T>
bool Entity::HasType() const
{
    return !components_.empty() &&
    components_.find(rttr::type::get<T>().get_id()) != components_.end();
}

#endif //GIGAENGINE_ENTITY_H
