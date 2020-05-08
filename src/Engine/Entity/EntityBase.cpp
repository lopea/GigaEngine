//
// Created by javier on 5/3/2020.
//

#include "EntityBase.h"
#include "../Component/ComponentManager.h"
#include <climits>

Entity::Entity() : id_(UINT_MAX)
{}

Entity::Entity(unsigned int id) : id_(id)
{}

unsigned int Entity::getID() const
{
    return id_;
}

bool Entity::operator==(unsigned int id) const
{
    return id_ == id;
}

bool operator==(unsigned int id_, const Entity &entity)
{
    return entity.id_ == id_;
}

bool Entity::operator==(const Entity &entity) const
{
    return entity.id_ == id_;
}

bool Entity::operator<(const Entity &entity) const
{
    return id_ < entity.id_;
}




