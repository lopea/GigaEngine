//
// Created by javier on 5/4/2020.
//

#ifndef GIGAENGINE_ENTITYLIST_H
#define GIGAENGINE_ENTITYLIST_H


#include "Entity.h"
#include <vector>

class EntityList
{
public:
    template<typename T, typename Func>
    void ForEach(Func function);

    template<typename T1, typename T2, typename Func>
    void ForEach(Func function);

    template<typename T>
    EntityList OfType();

    template<typename T1, typename T2>
    EntityList OfTypes();
    EntityList() = default;
    Entity& back();
private:
    void Add(Entity entity);
    explicit EntityList(std::vector<Entity>& entity);
    std::vector<Entity> entities_;
    friend class EntityManager;
};

template<typename T, typename Func>
void EntityList::ForEach(Func function)
{
    for(Entity& entity : entities_)
    {
        if(entity.HasType<T>())
        {
            function(entity.GetComponent<T>());
        }
    }


}

template<typename T1, typename T2>
EntityList EntityList::OfTypes()
{
    std::vector<Entity> lit;
    for (auto &it : entities_)
    {
        if(it.HasType<T1>() && it.HasType<T2>())
            lit.push_back(it);
    }
    return EntityList(lit);
}

template<typename T>
EntityList EntityList::OfType()
{
    std::vector<Entity> lit;
    for (auto &it : entities_)
    {
        if(it.HasType<T>())
            lit.push_back(it);
    }
    return EntityList(lit);
}





template<typename T1, typename T2, typename Func>
void EntityList::ForEach(Func function)
{
    std::for_each(entities_.begin(), entities_.end(), [function](Entity& entity)
    {
        if(entity.HasType<T1>() && entity.HasType<T2>())
        {
            function(entity.GetComponent<T1>(),entity.GetComponent<T2>());
        }
    });
}


#endif //GIGAENGINE_ENTITYLIST_H
