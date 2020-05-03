//
// Created by javier on 5/3/2020.
//

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include <vector>

typedef unsigned int Entity;
class EntityManager {
 public:
  static void Initialize();
  static Entity AddEntity();
  static void DestroyEntity(Entity entity);
  static void CheckForDestruction();
 private:
  EntityManager();
  static EntityManager manager_;
  std::vector<Entity> entities_;
  std::vector<Entity> destroy_;
  static bool Init_;
};

#endif //_ENTITYMANAGER_H_
