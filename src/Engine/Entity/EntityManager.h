//
// Created by javier on 5/3/2020.
//

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include <vector>
#include "EntityBase.h"
#include "EntityList.h"

class EntityManager {
 public:
  static void Initialize();
  static Entity& AddEntity();
  static void DestroyEntity(Entity entity);
  static void CheckForDestruction();
  static EntityList& GetEntities();
  EntityManager();
 private:

  static EntityManager manager_;
  EntityList entities_;
  std::vector<unsigned int> destroy_;
  static bool Init_;
};

#endif //_ENTITYMANAGER_H_
