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

    template<typename T>
    ReferenceEntityList OfType();

    template<typename T1, typename T2>
    ReferenceEntityList OfTypes();

    ReferenceEntityList() = default;


private:
    std::vector<Entity*> references_;
    explicit ReferenceEntityList(const std::vector<Entity*>& references);
    friend class EntityList;
};

template<typename Func>
void ReferenceEntityList::ForEach(Func function)
{
    for(auto& reference : references_)
    {
        function(*reference);
    }
}

template<typename T>
ReferenceEntityList ReferenceEntityList::OfType()
{
    std::vector<Entity*> ref;
    for (auto &reference : references_)
    {
        if(reference->HasType<T>())
        {
            ref.push_back(reference);
        }
    }

    return ReferenceEntityList(ref);
}

template<typename T1, typename T2>
ReferenceEntityList ReferenceEntityList::OfTypes()
{
    std::vector<Entity*> ref;
    for (auto &reference : references_)
    {
        if(reference->HasType<T1>() && reference->HasType<T2>())
        {
            ref.push_back(reference);
        }
    }

    return ReferenceEntityList(ref);
}



template<typename T, typename Func>
void ReferenceEntityList::ForEach(Func function)
{
    for (auto &reference : references_)
    {
        if(reference->HasType<T>())
        {
            function(reference->GetComponent<T>());
        }
    }
}

template<typename T1, typename T2, typename Func>
void ReferenceEntityList::ForEach(Func function)
{
    for (auto &reference : references_)
    {
        try
        {
            function(reference->GetComponent<T1>(), reference->GetComponent<T2>());
        }
        catch (ComponentNotFoundExeption& e) {}
    }
}

#endif //GIGAENGINE_ENTITYREFERENCELIST_H
