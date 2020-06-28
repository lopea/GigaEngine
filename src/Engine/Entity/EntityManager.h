//
// Created by javier on 5/3/2020.
//

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include <vector>
#include "EntityList.h"

typedef uint64_t Entity;

class EntityManager {
 public:
  static void Initialize();
  static Entity AddEntity();
  static void DestroyEntity(Entity entity);
  static void CheckForDestruction();
  static EntityList& GetEntities();
  EntityManager();
 private:
    static void Shutdown();
  static EntityManager manager_;
  EntityList entities_;
  std::set<Entity> destroy_;
  std::deque<Entity> available_;
  static bool Init_;
  friend class Engine;
};

#endif //_ENTITYMANAGER_H_
