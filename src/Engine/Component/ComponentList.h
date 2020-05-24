//
// Created by javier on 5/3/2020.
//

#ifndef _COMPONENTLIST_H_
#define _COMPONENTLIST_H_

#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include "ComponentExceptions.h"

typedef uint64_t Entity;


/*!
 * Handler to hold Componentlists without their unique type
 */
class GenericComponentList {};

/*!
 * Stores components of the same type based on their Entity associated with it.
 * @tparam T The type the component list will contain.
 */
template<typename T>
class ComponentList : public GenericComponentList
{
public:
    T* GetComponent(Entity entity);

    T* AddComponent(Entity entity);

    void RemoveComponent(Entity entity);

    std::vector<Entity> GetAllEnities();

    size_t size();

    std::vector<Entity> GetOverlappingEntities(std::vector<Entity>& reference);

private:
    std::unordered_map<Entity, T> components_;
    std::vector<Entity> entities_;
};

/*!
 * Remove an object based on the entity that is associated with said type.
 * @tparam T The type of the object.
 * @param entity The identifier for the object to destroy.
 */
template<typename T>
void ComponentList<T>::RemoveComponent(Entity entity)
{
  //find entity in the list
  auto& it = components_.find(entity);

  //if the entity exists, then remove it.
  if(components_.end() != it)
  {
    components_.erase(it);
    entities_.erase(std::find(entities_.begin(), entities_.end(), it));
  }

}


template<typename T>
T* ComponentList<T>::GetComponent(Entity entity)
{
    //get iterator containing the component to find
    auto it = components_.find(entity);

    // if the component exists,
    if (it != components_.end())
    {
        //send it off!
        return &it->second;
    }

    // nothing was found
    return nullptr;

}

/*!
 * Add a component to the list
 * @tparam T The component type
 * @param entity the identifier to find the new component
 * @return  the newly added component
 */
template<typename T>
T *ComponentList<T>::AddComponent(Entity entity)
{
    //check if the component already exists
    auto it = components_.find(entity);

    //return the one found if it exists
    if(it != components_.end())
        return &it->second;

    //component does not exist
    //add the entry to the component list
    components_.insert(std::pair<Entity,T>(entity, T()));
    entities_.push_back(entity);
    return &components_[entity];
}

template<typename T>
size_t ComponentList<T>::size()
{
    return components_.size();
}

template<typename T>
std::vector<Entity> ComponentList<T>::GetAllEnities()
{
  return entities_;
}

template<typename T>
std::vector<Entity> ComponentList<T>::GetOverlappingEntities(std::vector<Entity> &reference)
{
    std::vector<Entity> result;
    std::vector<Entity> ents = GetAllEnities();

    if(reference.empty() || ents.empty())
    {
        return result;
    }

    std::set_intersection(reference.begin(), reference.end(), ents.begin(), ents.end(), std::back_inserter(result));

    return result;

}

#endif //_COMPONENTLIST_H_
