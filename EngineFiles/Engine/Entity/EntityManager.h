//
// Created by javier on 5/3/2020.
//

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include <vector>
#include "EntityList.h"

typedef uint64_t Entity;

class EntityManager
{
public:
    static void Initialize();

    static Entity &AddEntity();

    static void DestroyEntity(Entity entity);

    static void CheckForDestruction();

    static EntityList &GetEntities();

    EntityManager();

private:
    static void Shutdown();

    static EntityManager manager_;
    EntityList entities_;
    std::vector<Entity> destroy_;
    std::vector<Entity> available_;
    static bool Init_;

    friend class Engine;
};

inline bool EntityManager::Init_ = false;
inline EntityManager EntityManager::manager_ = EntityManager();

/*!
 * Creates a new entity and adds the new entity to the entity manager.
 * @return Reference to the new entity created
 */
inline Entity& EntityManager::AddEntity ()
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

inline void EntityManager::Initialize ()
{
  Init_ = true;
  manager_.entities_.main_ = true;
}
inline void EntityManager::DestroyEntity (Entity entity)
{

}
inline void EntityManager::CheckForDestruction ()
{
  //TODO: do it.
}

inline EntityManager::EntityManager() : entities_()
{
}

/*!
 * Get all the entities currently in the game.
 *
 * This function is the gateway for systems to update the entities in the game.
 * @return All the current entities in the game
 */
inline EntityList &EntityManager::GetEntities()
{
  return manager_.entities_;
}

inline void EntityManager::Shutdown()
{
  Init_ = false;
  manager_.entities_.clear();
  manager_.available_.clear();
  manager_.entities_.clear();
}

#endif //_ENTITYMANAGER_H_
