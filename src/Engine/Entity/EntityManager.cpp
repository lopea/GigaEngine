//
// Created by javier on 5/3/2020.
//

#include "EntityManager.h"
#include <algorithm>


bool EntityManager::Init_ = false;
EntityManager EntityManager::manager_ = EntityManager();

/*!
 * Creates a new entity and adds the new entity to the entity manager.
 * @return Reference to the new entity created
 */
Entity& EntityManager::AddEntity ()
{
    //store next entity value
  static unsigned int id = 0;

  //add the new entity to the list
  manager_.entities_.Add(Entity(id));

  //add for next entity
  id++;

  //send it off!
  return manager_.entities_.back();
}

void EntityManager::Initialize ()
{
  Init_ = true;
  manager_.entities_.main_ = true;
}
void EntityManager::DestroyEntity (Entity entity)
{

}
void EntityManager::CheckForDestruction ()
{
  //TODO: do it.
}

EntityManager::EntityManager() : entities_()
{
}

/*!
 * Get all the entities currently in the game.
 *
 * This function is the gateway for systems to update the entities in the game.
 * @return All the current entities in the game
 */
EntityList &EntityManager::GetEntities()
{
    return manager_.entities_;
}


