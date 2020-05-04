//
// Created by javier on 5/3/2020.
//

#include "EntityBase.h"
#include "ComponentManager.h"


Entity::Entity () : id_(UINT_MAX){}
Entity::Entity (unsigned int id):id_(id){}

bool Entity::HasType (rttr::type &type) const
{
  return !types_.empty()
  && std::find(types_.begin(),types_.end(),type) != types_.end();
}
unsigned int Entity::getID () const
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

bool Entity::operator==(const Entity &entity)
{
    return entity.id_ == id_;
}

bool Entity::operator<(const Entity &entity) const
{
    return id_ < entity.id_;
}


