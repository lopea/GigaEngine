//
// Created by javier on 5/4/2020.
//

#include "EntityList.h"
EntityList::EntityList(std::vector<Entity>& entity) : entities_(entity)
{}

Entity &EntityList::back()
{
    return entities_.back();
}
void EntityList::Add(Entity entity)
{
    entities_.push_back(entity);
}

