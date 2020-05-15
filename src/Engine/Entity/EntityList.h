//
// Created by javier on 5/4/2020.
//

#ifndef GIGAENGINE_ENTITYLIST_H
#define GIGAENGINE_ENTITYLIST_H


#include "Entity.h"
#include "EntityReferenceList.h"
#include <omp.h>
#include <vector>
#include <algorithm>

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
    ReferenceEntityList OfType();

    template<typename T1, typename T2>
    ReferenceEntityList OfTypes();

    template<typename T>
    ReferenceEntityList ExcludeType();

    template<typename T1, typename T2>
    ReferenceEntityList ExcludeTypes();

    template<typename T1, typename T2, typename Func>
    void ParallelForEach(Func function);

    template<typename Func>
    void ParallelForEach(Func function);

    template<typename T, typename Func>
    void ParallelForEach(Func function);

    EntityList() = default;


private:
    void Add(Entity entity);

    explicit EntityList(std::vector<Entity> &entity);

    std::vector<Entity> entities_;

    friend class EntityManager;

    Entity &back();
};

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
  //for every entity in the list,
  for (Entity &entity : entities_)
  {

    //if the entity has a component of type T,
    if (entity.HasType<T>())
    {
      //execute the function with the type given.
      function(entity.GetComponent<T>());
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
ReferenceEntityList EntityList::OfTypes()
{
  //store the new list of references to types
  std::vector<Entity *> lit;

  //go through each entity in the list,
  for (auto &it : entities_)
  {
    //if the current entity has both types, add it to the list
    if (it.HasType<T1>() && it.HasType<T2>())
      lit.push_back(&it);
  }

  //create a new list and ship it.
  return ReferenceEntityList(lit);
}

/*!
 * Get all components that contain the of the same type given and store them in a new list.
 * @tparam T The type of Component to find in all the entities in the list.
 * @return A list with all entities that contain a component of type T
 */
template<typename T>
ReferenceEntityList EntityList::OfType()
{
  //store new list of references to types
  std::vector<Entity *> lit;
  for (auto &it : entities_)
  {
    if (it.HasType<T>())
      lit.push_back(&it);
  }
  return ReferenceEntityList(lit);
}

/*!
 * Get a list of entities that do not contain a component type given.
 * @tparam T The type of component to exclude
 * @return A new list that contains all the entities in this list that do not contain the component type given.
 */
template<typename T>
ReferenceEntityList EntityList::ExcludeType()
{
  std::vector<Entity *> lit;
  for (auto &it : entities_)
  {
    if (!it.HasType<T>())
      lit.push_back(&it);
  }
  return ReferenceEntityList(lit);
}

/*!
 * Get a list of entities that do not contain 2 different types of components.
 * @tparam T1 One type of component that will get excluded.
 * @tparam T2 Another type of component that will get excluded from the new list.
 * @return A new list of entities that do not contain 2 different types of components.
 */
template<typename T1, typename T2>
ReferenceEntityList EntityList::ExcludeTypes()
{
  //store the new list of references to types
  std::vector<Entity *> lit;

  //go through each entity in the list,
  for (auto &it : entities_)
  {
    //if the current entity does not have both types, add it to the list
    if (!it.HasType<T1>() && !it.HasType<T2>())
      lit.push_back(&it);
  }

  //create a new list and ship it.
  return ReferenceEntityList(lit);

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

  for (auto &entity : entities_)
  {
    if (entity.HasType<T1>() && entity.HasType<T2>())
      function(entity.GetComponent<T1>(), entity.GetComponent<T2>());
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
#pragma omp parallel for schedule(static) shared(function) default(none)
  for (int i = 0; i < entities_.size(); ++i)
  {
    Entity &entity = entities_[i];

    //this is pretty bad but idk at this point its really fast
    if (entity.HasType<T1>() && entity.HasType<T2>())
      function(entity.GetComponent<T1>(), entity.GetComponent<T2>());
  }
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
#pragma omp parallel for schedule(static) shared(function) default(none)
  for (int i = 0; i < entities_.size(); ++i)
  {
    Entity &entity = entities_[i];

    if (entity.HasType<T>())
      function(entity.GetComponent<T>());
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
