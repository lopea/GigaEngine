//
// Created by javier on 5/3/2020.
//

#ifndef _COMPONENTLIST_H_
#define _COMPONENTLIST_H_

#include <map>
#include "EntityBase.h"
#include "ComponentExceptions.h"


/*!
 * Handler to hold Componentlists without their unique type
 */
class GenericComponentList
{
};

/*!
 * Stores components of the same type based on their Entity associated with it.
 * @tparam T The type the component list will contain.
 */
template<typename T>
class ComponentList : public GenericComponentList
{
public:
    T& GetComponent(Entity entity);

    T& AddComponent(Entity entity);

    void RemoveComponent(Entity entity);

private:
    std::map<Entity, T> components_;
};

/*!
 * Remove an object based on the entity that is associated with said type.
 * @tparam T The type of the object.
 * @param entity The identifier for the object to destroy.
 */
template<typename T>
void ComponentList<T>::RemoveComponent(Entity entity)
{
    components_.erase(entity);
}


template<typename T>
T& ComponentList<T>::GetComponent(Entity entity)
{
    //get iterator containing the component to find
    auto it = components_.find(entity);

    // if the component exists,
    if (it != components_.end())
    {
        //send it off!
        return it->second;
    }

    // nothing was found, throw an exception
    throw ComponentNotFoundExeption(rttr::type::get<T>());

}

/*!
 * Add a component to the list
 * @tparam T The component type
 * @param entity the identifier to find the new component
 * @return  the newly added component
 */
template<typename T>
T &ComponentList<T>::AddComponent(Entity entity)
{
    //check if the component already exists
    auto it = components_.find(entity);

    //return the one found if it exists
    if(it != components_.end())
        return it->second;

    //component does not exist
    //add the entry to the component list
    components_.insert(std::pair<Entity,T>(entity, T()));

    return components_[entity];
}

#endif //_COMPONENTLIST_H_
