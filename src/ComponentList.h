//
// Created by javier on 5/3/2020.
//

#ifndef _COMPONENTLIST_H_
#define _COMPONENTLIST_H_

#include <map>
#include "Entity.h"

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
    bool GetComponent(Entity entity, T &&output) ;

    T &AddComponent(Entity entity);

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

/*!
 * Get a component based on the entity that is associated with.
 * If a component has been found, it will store the result in the output parameter
 * @tparam T The type of component
 * @param entity the entity that identifies what component to get
 * @param output if a component has been found, it will set the component found to this parameter
 * @return true if a component has been found, false otherwise.
 */
template<typename T>
bool ComponentList<T>::GetComponent(Entity entity, T &&output)
{
    auto it = components_.find(entity);
    if (it != components_.end())
    {
        output = it->second;
        return true;
    }
    return false;

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
    //add the entry to the component list
    components_.insert(std::pair<Entity,T>(entity, T()));

    return components_[entity];
}

#endif //_COMPONENTLIST_H_
