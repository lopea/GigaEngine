//
// Created by javier on 5/3/2020.
//

#ifndef GIGAENGINE_ENTITY_H
#define GIGAENGINE_ENTITY_H
#include "EntityBase.h"
#include "../Component/ComponentExceptions.h"
#include "../Component/ComponentManager.h"
#include <rttr/type>

/*!
 * Get the component that is part of this entity based on its type
 * @tparam T Type of component to find in the entity
 * @return Reference to the component of type T that is part of the
 *         entity. if no component is found, the function throws a
 *         ComponentNotFoundException
 */
template<typename T>
T& Entity::GetComponent ()
{
    auto it = components_.find(rttr::type::get<T>().get_id());

    if(it != components_.end())
        return *static_cast<T*>(it->second);

    throw ComponentNotFoundException(rttr::type::get<T>());
    //return ComponentManager::GetComponent<T>(*this);
}

/*!
 * Add a component to the entity of a certain type.<br> The function will
 * do nothing if a component of the same type already exists in the
 * entity.
 * @tparam T The type of component to add to this entity
 * @return Reference to a new component of type T that corresponds
 *         to this entity. if a component of type T already exists,
 *         then the function will return a reference to that component.
 */
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

/*!
 * Check if a component of type T already exists in this entity.
 * @tparam T The type to find
 * @return True if a component of type T exists in the entity, false
 * otherwise
 */
template<typename T>
bool Entity::HasType() const
{
    return !components_.empty() &&
    components_.find(rttr::type::get<T>().get_id()) != components_.end();
}

#endif //GIGAENGINE_ENTITY_H
