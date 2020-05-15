//
// Created by javier on 5/7/2020.
//

#ifndef GIGAENGINE_ENTITYREFERENCELIST_H
#define GIGAENGINE_ENTITYREFERENCELIST_H

#include "EntityBase.h"
#include "../Component/ComponentExceptions.h"

/*!
 * Stores references to entities in EntityLists
 */
class ReferenceEntityList
{
public:
    template<typename Func>
    void ForEach(Func function);

    template<typename T, typename Func>
    void ForEach(Func function);

    template<typename T1, typename T2, typename Func>
    void ForEach(Func function);

    template<typename Func>
    void ParallelForEach(Func function);

    template<typename T, typename Func>
    void ParallelForEach(Func function);

    template<typename T1, typename T2, typename Func>
    void ParallelForEach(Func function);

    template<typename T>
    ReferenceEntityList OfType();

    template<typename T1, typename T2>
    ReferenceEntityList OfTypes();

    ReferenceEntityList() = default;


private:
    std::vector<Entity *> references_;

    explicit ReferenceEntityList(const std::vector<Entity *> &references);

    friend class EntityList;
};



template<typename T>
ReferenceEntityList ReferenceEntityList::OfType()
{
  std::vector<Entity *> ref;
  for (auto &reference : references_)
  {
    if (reference->HasType<T>())
    {
      ref.push_back(reference);
    }
  }

  return ReferenceEntityList(ref);
}

/*!
 * Get all entities that contain 2 different types of components and store them in a new list.
 * @tparam T1 One Component type.
 * @tparam T2 Another component type.
 * @return a list containing all entities with components of the types given.
 */
template<typename T1, typename T2>
ReferenceEntityList ReferenceEntityList::OfTypes()
{
  std::vector<Entity *> ref;
  for (auto &reference : references_)
  {
    if (reference->HasType<T1>() && reference->HasType<T2>())
    {
      ref.push_back(reference);
    }
  }

  return ReferenceEntityList(ref);
}

/*!
 * Goes through all the entities in this list and calls the function given.
 * @tparam Func Represents the type of function that gets called on all the entities in the list.<br>
 *              Function must contain an Entity reference parameter and return nothing.<br>
 *              example: myFunc(Entity& ent) or [ ](Entity& ent){ //... }
 * @param function the function that gets called on all entities on this list.
 */
template<typename Func>
void ReferenceEntityList::ForEach(Func function)
{
  for (auto &reference : references_)
  {
    function(*reference);
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
void ReferenceEntityList::ForEach(Func function)
{
  for (auto &reference : references_)
  {
    if (reference->HasType<T>())
    {
      function(reference->GetComponent<T>());
    }
  }
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
void ReferenceEntityList::ForEach(Func function)
{
  for (auto &reference : references_)
  {
    try
    {
      function(reference->GetComponent<T1>(), reference->GetComponent<T2>());
    }
    catch (ComponentNotFoundExeption &e)
    {}
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
void ReferenceEntityList::ParallelForEach(Func function)
{
#pragma omp parallel for schedule(static) shared(function) default(none)
  for (int i = 0; i < references_.size(); ++i)
  {
    function(*references_[i]);
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
void ReferenceEntityList::ParallelForEach(Func function)
{
#pragma omp parallel for schedule(static) shared(function) default(none)
  for (int i = 0; i < references_.size(); ++i)
  {
    Entity &entity = *references_[i];

    if (entity.HasType<T>())
      function(entity.GetComponent<T>());
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
void ReferenceEntityList::ParallelForEach(Func function)
{
#pragma omp parallel for schedule(static) shared(function) default(none)
  for (int i = 0; i < references_.size(); ++i)
  {
    Entity &entity = *references_[i];

    //this is pretty bad but idk at this point its really fast
    if (entity.HasType<T1>() && entity.HasType<T2>())
      function(entity.GetComponent<T1>(), entity.GetComponent<T2>());
  }
}

#endif //GIGAENGINE_ENTITYREFERENCELIST_H
