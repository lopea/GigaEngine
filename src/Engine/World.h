//
// Created by Javier Sandoval on 8/21/2020.
//

#ifndef _WORLD_H_
#define _WORLD_H_
#include "Entity/EntityManager.h"
#include "EventManager.h"
#include "Systems/SystemManager.h"
enum class WorldType
{
  Basic,
  System
};
class World
{
 public:
  World(WorldType type);
  EntityManager& entityManager;
  ComponentManager& componentManager;
  EventManager& eventManager;
  SystemManager& systemManager;
};

#endif //_WORLD_H_
