//
// Created by javier on 5/3/2020.
//

#include "EntityManager.h"
#include <algorithm>


bool EntityManager::Init_ = false;
EntityManager EntityManager::manager_ = EntityManager();

Entity& EntityManager::AddEntity ()
{
  static unsigned int id = 0;
  manager_.entities_.push_back(Entity(id));
  id++;
  return manager_.entities_.back();
}
void EntityManager::Initialize ()
{
  Init_ = true;
}
void EntityManager::DestroyEntity (Entity entity)
{
  if(std::find(manager_.destroy_.begin(),manager_.destroy_.end(), entity) != manager_.destroy_.end())
    manager_.destroy_.push_back(entity.getID());
}
void EntityManager::CheckForDestruction ()
{
  //TODO: do it.
}

EntityManager::EntityManager () {}
