//
// Created by javier on 5/3/2020.
//

#ifndef _COMPONENTMANAGER_H_
#define _COMPONENTMANAGER_H_

#include <unordered_map>
#include <rttr/type>
#include "ComponentList.h"
#include "ComponentBase.h"

class ComponentManager
{
public:
    static void Initialize();

    static void Shutdown();

    template<typename T>
    static T& GetComponent(Entity& entity);

    template<typename T>
    static T& AddComponent(Entity& entity);

private:
    ComponentManager() = default;

    static ComponentManager manager_;
    std::unordered_map<rttr::type, GenericComponentList *> lists_;
    static bool Init_;
};

template<typename T>
 T& ComponentManager::GetComponent(Entity& entity)
{
    //get the type of the component
    rttr::type t = rttr::type::get<T>();

    //if the type does not derive from component,
    if (!t.is_derived_from<ComponentBase>())
    {
        //throw exception
       throw TypeNotComponentException(t);
    }

    //find the list corresponding to the type
    auto it = manager_.lists_.find(t);

    //if a list has been found ...
    if (it != manager_.lists_.end())
    {
        //cast the component list based on the type
        ComponentList<T> *list = static_cast<ComponentList<T> *>(it->second);

        //get the component from the list and return
        return list->GetComponent(entity);
    }

    //nothing has been found, throw exeption
    throw ComponentNotFoundExeption(t);
}

template<typename T>
 T &ComponentManager::AddComponent(Entity& entity)
{
    //get the type of T
    rttr::type t = rttr::type::get<T>();

    //check if the type is valid
    if (!t.is_derived_from<ComponentBase>())
    {
        //TODO: Throw "type not a component" exception
    }

    //go through list and check if list is there
    auto it = manager_.lists_.find(t);

    //if a list has been found,
    if (it != manager_.lists_.end())
    {
        //cast the list to the correct type
        ComponentList<T> *list = static_cast<ComponentList<T> *>(it->second);

        //add the component to the list and return the result
        return list->AddComponent(entity);
    }

    //list of type does not exist, add it to the manager
    ComponentList<T> *newList = new ComponentList<T>;

    //add the new list
    manager_.lists_.insert(std::pair<rttr::type, GenericComponentList *>(
            t, static_cast<GenericComponentList *>(newList)));

    //add the new entity and return the type created
    return newList->AddComponent(entity);
}

#endif //_COMPONENTMANAGER_H_
