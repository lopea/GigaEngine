//
// Created by javier on 5/4/2020.
//

#ifndef GIGAENGINE_ENTITYLIST_H
#define GIGAENGINE_ENTITYLIST_H


#include "Entity.h"
#include "EntityReferenceList.h"

#include <vector>


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



    EntityList() = default;


private:
    void Add(Entity entity);
    explicit EntityList(std::vector<Entity>& entity);
    std::vector<Entity> entities_;
    friend class EntityManager;
    Entity& back();
};



template<typename Func>
void EntityList::ForEach(Func function)
{

    for(int i = 0; i < entities_.size(); ++i)
    {
        Entity& entity = entities_[i];
        //execute the function given
        function(entity);
    }
}

template<typename T, typename Func>
void EntityList::ForEach(Func function)
{
    //for every entity in the list,

    for(Entity& entity : entities_)
    {
        //if the entity has the component type given,
        if (entity.HasType<T>())
        {
            //execute the function with the type given.
            function(entity.GetComponent<T>());
        }
    }
}

template<typename T1, typename T2>
ReferenceEntityList EntityList::OfTypes()
{
    //store the new list of references to types
    std::vector<Entity*> lit;

    //go through each entity in the list,
    for (auto &it : entities_)
    {
        //if the current entity has both types, add it to the list
        if(it.HasType<T1>() && it.HasType<T2>())
            lit.push_back(&it);
    }

    //create a new list and ship it.
    return ReferenceEntityList(lit);
}

template<typename T>
ReferenceEntityList EntityList::OfType()
{
    //store new list of references to types
    std::vector<Entity*> lit;
    for (auto &it : entities_)
    {
        if(it.HasType<T>())
            lit.push_back(&it);
    }
    return ReferenceEntityList(lit);
}

template<typename T>
ReferenceEntityList EntityList::ExcludeType()
{
    std::vector<Entity*> lit;
    for (auto &it : entities_)
    {
        if(!it.HasType<T>())
            lit.push_back(&it);
    }
    return ReferenceEntityList(lit);
}

template<typename T1, typename T2>
ReferenceEntityList EntityList::ExcludeTypes()
{
    //store the new list of references to types
    std::vector<Entity*> lit;

    //go through each entity in the list,
    for (auto &it : entities_)
    {
        //if the current entity does not have both types, add it to the list
        if(!it.HasType<T1>() && !it.HasType<T2>())
            lit.push_back(&it);
    }

    //create a new list and ship it.
    return ReferenceEntityList(lit);
}


template<typename T1, typename T2, typename Func>
void EntityList::ForEach(Func function)
{
    for(int i = 0; i < entities_.size(); ++i)
    {
        Entity& entity = entities_[i];
        if(entity.HasType<T1>() && entity.HasType<T2>())
        {
            function(entity.GetComponent<T1>(),entity.GetComponent<T2>());
        }
    }
}


#endif //GIGAENGINE_ENTITYLIST_H
