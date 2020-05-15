//
// Created by javier on 5/4/2020.
//

#include "EntityList.h"

/*!
 * EntityList Conversion Constructor, convert a vector of entities to a EntityList
 * @param entity the vector of entities to add to a list
 */
EntityList::EntityList(std::vector<Entity>& entity) : entities_(entity)
{}

/*!
 * Gets the last entity in the list, for internal use only
 * @return the last entity in the list
 */
Entity &EntityList::back()
{
    return entities_.back();
}

/*!
 * Adds a new entity to the list, for internal use only
 * @param entity the entity to add to the list
 */
void EntityList::Add(Entity entity)
{
    entities_.push_back(entity);
}

