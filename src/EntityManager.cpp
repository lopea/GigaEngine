//
// Created by javier on 5/3/2020.
//

#include "EntityManager.h"
#include <algorithm>


bool EntityManager::Init_ = false;
EntityManager EntityManager::manager_ = EntityManager();

Entity EntityManager::AddEntity ()
{
  static Entity newE = 0;
  manager_.entities_.push_back(newE);
  Entity ret = newE;
  newE++;
  return ret;
}
void EntityManager::Initialize ()
{
  Init_ = true;
}
void EntityManager::DestroyEntity (Entity entity)
{
  if(std::find(manager_.destroy_.begin(),manager_.destroy_.end(), entity) != manager_.destroy_.end())
    manager_.destroy_.push_back(entity);
}
void EntityManager::CheckForDestruction ()
{
  //TODO: do it.
}

EntityManager::EntityManager () {}
