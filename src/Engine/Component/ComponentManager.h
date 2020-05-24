//
// Created by javier on 5/3/2020.
//

#ifndef _COMPONENTMANAGER_H_
#define _COMPONENTMANAGER_H_

#include <unordered_map>
#include <rttr/type>
#include "ComponentList.h"
#include "Component.h"


typedef uint64_t Entity;

class ComponentManager
{
public:
    static void Initialize()
    {
        Init_ = true;
    }

    static void Shutdown()
    {
        Init_ = false;
    }

    template<typename T>
    static T *GetComponent(Entity entity);

    template<typename T>
    static T *AddComponent(Entity entity);

private:
    friend class EntityList;

    template<typename T>
    static ComponentList<T>* GetList();

    ComponentManager() = default;
    static ComponentManager manager_;
    std::unordered_map<rttr::type, GenericComponentList *> lists_;
    static bool Init_;
};

inline ComponentManager ComponentManager::manager_;
inline bool ComponentManager::Init_ = false;

template<typename T>
T *ComponentManager::GetComponent(Entity entity)
{
    //get the type of the component
    rttr::type t = rttr::type::get<T>();

    //if the type does not derive from component,
    if (!t.is_derived_from<Component>())
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
    return nullptr;
}

template<typename T>
T *ComponentManager::AddComponent(Entity entity)
{
    //get the type of T
    rttr::type t = rttr::type::get<T>();

    //check if the type is valid
    if (!t.is_derived_from<Component>())
    {
        throw TypeNotComponentException(t);
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

template<typename T>
ComponentList<T> *ComponentManager::GetList()
{
    auto it = manager_.lists_.find(rttr::type::get<T>());
    if(it != manager_.lists_.end())
    {
        return static_cast<ComponentList<T> *>(it->second);
    }
    return nullptr;
}

#endif //_COMPONENTMANAGER_H_
