//
// Created by javier on 5/3/2020.
//

#ifndef GIGAENGINE_ENTITY_H
#define GIGAENGINE_ENTITY_H
#include "EntityBase.h"
#include "ComponentManager.h"
#include <rttr/type>
template<typename T>
T& Entity::GetComponent ()
{
    rttr::type t = rttr::type::get<T>();
    int count = 0;
    for(auto& it : types_)
    {
        if(it == t)
        {
            return *static_cast<T*>(components_[count]);
        }
        count++;
    }

    throw ComponentNotFoundExeption(t);
    //return ComponentManager::GetComponent<T>(*this);
}
template<typename T>
T &Entity::AddComponent ()
{
    rttr::type t = rttr::type::get<T>();

    T& res = ComponentManager::AddComponent<T>(*this);

    //add type to the list
    components_.push_back(&res);
    types_.push_back(t);

    //add type to the list
    return *static_cast<T*>(components_.back());
}

template<typename T>
bool Entity::HasType() const
{
    return !types_.empty() && std::find(types_.begin(),types_.end(), rttr::type::get<T>()) != types_.end();
}
#endif //GIGAENGINE_ENTITY_H
