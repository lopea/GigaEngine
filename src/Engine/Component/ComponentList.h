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
class GenericComponentList
{
public :
    virtual ~GenericComponentList() = default;
};

/*!
 * Stores components of the same type based on their Entity associated with it.
 * @tparam T The type the component list will contain.
 */
template<typename T>
class ComponentList : public GenericComponentList
{
public:
    T *GetComponent(Entity entity);

    T *AddComponent(Entity entity);

    void RemoveComponent(Entity entity);

    size_t size();

    std::vector<Entity> GetOverlappingEntities(std::vector<Entity> reference);

    bool empty() const;

private:
    std::vector<T> components_;
    std::unordered_map<Entity, size_t> EntityToIndex_;
    std::deque<size_t> available_;
    std::set<Entity> entities_;
    friend class ComponentManager;

    void clear();
};

/*!
 * Remove an object based on the entity that is associated with said type.
 * @tparam T The type of the object.
 * @param entity The identifier for the object to destroy.
 */
template<typename T>
void ComponentList<T>::RemoveComponent(Entity entity)
{
  available_.push_back(EntityToIndex_[entity]);
  EntityToIndex_.erase(entity);
  entities_.erase(entity);
}


template<typename T>
T *ComponentList<T>::GetComponent(Entity entity)
{
  //get iterator containing the component to find
  auto it = EntityToIndex_.find(entity);

  // if the component exists,
  if (it != EntityToIndex_.end())
  {
    //send it off!
    return & components_[it->second];
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
  auto it = EntityToIndex_.find(entity);
  if(it != EntityToIndex_.end())
    return &components_[it->second];

  size_t currSize;
  if(!available_.empty())
  {
    currSize = available_.back();
    available_.pop_back();
    components_[currSize] = T(entity);
  }
  else
  {
    currSize = components_.size();
    components_.push_back(T(entity));
  }
  EntityToIndex_[entity] = currSize;
  entities_.insert(entity);

  return &components_[currSize];
}

template<typename T>
size_t ComponentList<T>::size()
{
  return components_.size();
}

template<typename T>
std::vector<Entity> ComponentList<T>::GetOverlappingEntities(std::vector<Entity> reference)
{
  std::vector<Entity> result;

  if (!reference.empty() && !entities_.empty())
    std::set_intersection(reference.begin(), reference.end(), entities_.begin(), entities_.end(), std::back_inserter(result));

  return result;
}

template<typename T>
void ComponentList<T>::clear()
{
  components_.clear();
  EntityToIndex_.clear();
  entities_.clear();
}

template<typename T>
bool ComponentList<T>::empty() const
{
  return components_.empty();
}




#endif //_COMPONENTLIST_H_
