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
Entity EntityManager::AddEntity ()
{
    //store next entity value
  static Entity id = 0;
  if(!manager_.available_.empty())
  {
      manager_.entities_.Add(manager_.available_.front());
      manager_.available_.pop_front();
  }
  else
  {
      //add the new entity to the list
      manager_.entities_.Add(id);

      //add for next entity
      id++;

  }
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
    manager_.destroy_.insert(entity);
}
void EntityManager::CheckForDestruction ()
{
  for(Entity ent : manager_.destroy_)
  {
      ComponentManager::RemoveComponents(ent);
  }
  manager_.available_.insert(manager_.available_.begin(),manager_.destroy_.begin(), manager_.destroy_.end());
  manager_.destroy_.clear();
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

void EntityManager::Shutdown()
{
  Init_ = false;
  manager_.entities_.clear();
  manager_.available_.clear();
  manager_.entities_.clear();
}


