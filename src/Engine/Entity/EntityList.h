//
// Created by javier on 5/4/2020.
//

#ifndef GIGAENGINE_ENTITYLIST_H
#define GIGAENGINE_ENTITYLIST_H


#include "../Component/ComponentManager.h"
#include "../Tag/TagBase.h"
#include "../Tag/TagManager.h"
#include <omp.h>
#include <vector>
#include <algorithm>

using Entity = uint64_t;

class EntityList
{
public:
    template<typename Func>
    void ForEach(Func function);

    template<typename T, typename Func>
    void ForEach(Func function);

    template<typename T1, typename T2, typename Func>
    void ForEach(Func function);

    template<typename T>
    EntityList OfType() const;

    template<typename T1, typename T2>
    EntityList OfTypes() const;

    template<typename T>
    EntityList ExcludeType() const;

    template<typename T1, typename T2>
    EntityList ExcludeTypes() const;

    template<typename T1, typename T2, typename Func>
    void ParallelForEach(Func function);

    template<typename Func>
    void ParallelForEach(Func function);

    template<typename T, typename Func>
    void ParallelForEach(Func function);

    EntityList() = default;

    bool empty() const;

    size_t size() const;


private:
    void Add(Entity entity);

    explicit EntityList(std::vector<Entity> entity);

    std::vector<Entity> entities_;

    friend class EntityManager;

    bool main_;

    Entity &back();

    void clear();

};

/*!
 * EntityList Conversion Constructor, convert a vector of entities to a EntityList
 * @param entity the vector of entities to add to a list
 */
inline EntityList::EntityList(std::vector<Entity> entity) : entities_(entity), main_(false)
{}

/*!
 * Gets the last entity in the list, for internal use only
 * @return the last entity in the list
 */
inline Entity &EntityList::back()
{
  return entities_.back();
}

/*!
 * Adds a new entity to the list, for internal use only
 * @param entity the entity to add to the list
 */
inline void EntityList::Add(Entity entity)
{
  entities_.push_back(entity);
}


/*!
 * Goes through all the entities in this list and calls the function given.
 * @tparam Func Represents the type of function that gets called on all the entities in the list.<br>
 *              Function must contain an Entity reference parameter and return nothing.<br>
 *              example: myFunc(Entity& ent) or [ ](Entity& ent){ //... }
 * @param function the function that gets called on all entities on this list.
 */
template<typename Func>
void EntityList::ForEach(Func function)
{
  //go through all entities
  for (auto &entity : entities_)
  {
    //execute the function given
    function(entity);
  }
}

/*!
 * Go through all entities in this list, get a specific component from them and call a function based on that component.<br>
 * If the certain entity does not have that type of component, it will be skipped.
 * @tparam T Represents the type of component to get from the entities in this list
 * @tparam Func Represents the type of function to pass in. <br>
 *              Function type must contain a reference parameter of type T and return nothing.<br>
 *              Example: myFunc(T& component) or [ ](T& component){ //... }
 * @param function The function to call on each entity in this list
 */
template<typename T, typename Func>
void EntityList::ForEach(Func function)
{
  //get the list of components of type T
  ComponentList<T> *list = ComponentManager::GetList<T>();

  //if the list exists
  if (list)
  {
    //get all entities that are inside the list
    std::vector<Entity> ents = list->GetOverlappingEntities(entities_);

    //for every entity in the list,
    for (Entity entity : ents)
    {
      //get the component
      T *comp = ComponentManager::GetComponent<T>(entity);

      //call the function on the component
      if (comp)
      {
        function(*comp);
      }
    }
  }
}

/*!
 * Get all entities that contain 2 different types of components and store them in a new list.
 * @tparam T1 One Component type.
 * @tparam T2 Another component type.
 * @return a list containing all entities with components of the types given.
 */
template<typename T1, typename T2>
EntityList EntityList::OfTypes() const
{
  //store the new list of references to types
  std::vector<Entity> list;

  //get reference of all components of both types
  ComponentList<T1> *list1 = ComponentManager::GetList<T1>();
  ComponentList<T2> *list2 = ComponentManager::GetList<T2>();

  //if they both exist
  if (list1 && list2)
  {
    //If entity list is the main one,
    if (main_)
    {
      //get all overlapping entities from both components and store them into an EntityList
      return EntityList(list1->GetOverlappingEntities(list2->GetAllEnities()));
    }
    //Get the common entities from this list and T1's components
    std::vector<Entity> ent1 = list1->GetOverlappingEntities(entities_);

    //get the common entities from the last list and T2's components
    std::vector<Entity> ent2 = list2->GetOverlappingEntities(ent1);

    //send an EntityList with the overlapping Entities
    return EntityList(ent2);

  }

  //one (or both) entities do not have a list yet, return an empty list
  return EntityList();
}

/*!
 * Get all components that contain the of the same type given and store them in a new list.
 * @tparam T The type of Component to find in all the entities in the list.
 * @return A list with all entities that contain a component of type T
 */
template<typename T>
EntityList EntityList::OfType() const
{
  rttr::type t = rttr::type::get<T>();
  if(t.is_derived_from<TagBase>())
  {
    TagList<T>* list = TagManager::GetList<T>();
    if(list)
    {
      std::vector<Entity> ents = list->GetOverlappingEntities(entities_);

      return EntityList(ents);
    }
    return EntityList();
  }
  ComponentList<T> *list = ComponentManager::GetList<T>();

  if (list)
  {

    //find overlapping entities between the component and this list
    std::vector<Entity> ents = list->GetOverlappingEntities(entities_);

    //send an EntityList that contains all entities from this list that has this type
    return EntityList(ents);
  }

  return EntityList();
}

/*!
 * Get a list of entities that do not contain a component type given.
 * @tparam T The type of component to exclude
 * @return A new list that contains all the entities in this list that do not contain the component type given.
 */
template<typename T>
EntityList EntityList::ExcludeType() const
{
  EntityList result;

  ComponentList<T> *list = ComponentManager::GetList<T>();
  if (list)
  {

  }

  return result;
}

/*!
 * Get a list of entities that do not contain 2 different types of components.
 * @tparam T1 One type of component that will get excluded.
 * @tparam T2 Another type of component that will get excluded from the new list.
 * @return A new list of entities that do not contain 2 different types of components.
 */
template<typename T1, typename T2>
EntityList EntityList::ExcludeTypes() const
{
  return EntityList();
}

/*!
 * Goes through all the entities in the list, Gets the components of type T1 and T2, and calls a function with those
 * components as parameters. If the entity does not contain both, it will be skipped.
 * @tparam T1 The first component type
 * @tparam T2 The second component type
 * @tparam Func The type of function to call on all entities.
 *              The function must be void and  have a reference to T1 and T2 as parameters IN THAT ORDER.<br>
 *              Example: myFunc(T1& comp1, T2& comp2) or [ ] (T1& comp1, T2 comp2) { //... }
 * @param function the function to call on all entities that contain T1 and T2
 */
template<typename T1, typename T2, typename Func>
void EntityList::ForEach(Func function)
{
  ComponentList<T1> *list1 = ComponentManager::GetList<T1>();
  ComponentList<T2> *list2 = ComponentManager::GetList<T2>();

  if(entities_.empty() || !list2 || !list1)
    return;

  for (auto &entity : entities_)
  {
    T1 *comp1 = list1->GetComponent(entity);
    T2 *comp2 = list2->GetComponent(entity);

    if (comp1 && comp2)
    {
      function(*comp1, *comp2);
    }
  }
}

/*!
 * Goes through all the entities in the list in parallel, Gets the components of type T1 and T2, and calls a function with those
 * components as parameters. If the entity does not contain both, it will be skipped.<br>
 * Be careful, issues can arise when you parallelize code. If issues do arise, use ForEach instead.
 * @tparam T1 The first component type
 * @tparam T2 The second component type
 * @tparam Func The type of function to call on all entities.
 *              The function must be void and  have a reference to T1 and T2 as parameters IN THAT ORDER.<br>
 *              Example: myFunc(T1& comp1, T2& comp2) or [ ] (T1& comp1, T2& comp2) { //... }
 * @param function the function to call on all entities that contain T1 and T2
 */
template<typename T1, typename T2, typename Func>
void EntityList::ParallelForEach(Func function)
{
  ComponentList<T1> *list1 = ComponentManager::GetList<T1>();
  ComponentList<T2> *list2 = ComponentManager::GetList<T2>();


  if(!list1 || !list2 || entities_.empty())
    return;

  #pragma omp parallel for schedule(static) shared(function, list1, list2) default(none)
  for (int i = 0; i < entities_.size(); ++i)
  {
    Entity entity = entities_[i];

    T1 *comp1 = list1->GetComponent(entity);
    T2 *comp2 = list2->GetComponent(entity);

    if (comp1 && comp2)
    {
      function(*comp1, *comp2);
    }
  }
}

inline size_t EntityList::size() const
{
  return entities_.size();
}

inline bool EntityList::empty() const
{
  return entities_.empty();
}

inline void EntityList::clear()
{
  return entities_.clear();
}

/*!
 * Go through all entities in this list in parallel, get a specific component from them and call a function based on that component.<br>
 * If the certain entity does not have that type of component, it will be skipped.<br>
 * Be careful, issues can arise when you parallelize code. If issues do arise, use ForEach instead.
 * @tparam T Represents the type of component to get from the entities in this list
 * @tparam Func Represents the type of function to pass in. <br>
 *              Function type must contain a reference parameter of type T and return nothing.<br>
 *              Example: myFunc(T& component) or [ ](T& component){ //... }
 * @param function The function to call on each entity in this list
 */
template<typename T, typename Func>
void EntityList::ParallelForEach(Func function)
{
  ComponentList<T> *list = ComponentManager::GetList<T>();
  if (list)
  {
#pragma omp parallel for schedule(static) shared(function, list) default(none)
    for (int i = 0; i < entities_.size(); ++i)
    {
      Entity entity = entities_[i];

      T *comp = list->GetComponent(entity);

      if (comp)
      {
        function(*comp);
      }
    }
  }
}

/*!
 * Goes through all the entities in this list in parallel and calls the function given.<br>
 * Be careful, issues can arise when you parallelize code. If issues do arise, use ForEach instead.
 * @tparam Func Represents the type of function that gets called on all the entities in the list.<br>
 *              Function must contain an Entity reference parameter and return nothing.<br>
 *              example: myFunc(Entity& ent) or [ ](Entity& ent){ //... }
 * @param function the function that gets called on all entities on this list.
 */
template<typename Func>
void EntityList::ParallelForEach(Func function)
{
#pragma omp parallel for schedule(static) shared(function) default(none)
  for (int i = 0; i < entities_.size(); ++i)
  {
    function(entities_[i]);
  }
}


#endif //GIGAENGINE_ENTITYLIST_H
