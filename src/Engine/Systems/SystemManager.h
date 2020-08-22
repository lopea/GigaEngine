//
// Created by Javier Sandoval on 8/21/2020.
//

#ifndef _SYSTEMMANAGER_H_
#define _SYSTEMMANAGER_H_

#include <rttr/type>
#include "SystemBase.h"
#include "../World.h"
class SystemManager
{
 public:

  template<typename T>
  void AddSystem();

  template<typename T>
  void RemoveSystem();

  void Update();
  void Init();
  void Exit();

 private:
  World& world_;
  friend class World;
  explicit SystemManager(World& world);
  std::unordered_map<rttr::type, SystemBase*> systems_;
};

template<typename T>
void SystemManager::AddSystem()
{
  rttr::type type = rttr::type::get<T>();
  systems_[type] = new T();
  systems_[type]->Init();
}

template<typename T>
void SystemManager::RemoveSystem()
{
  rttr::type type = rttr::type::get<T>();
  delete static_cast<T*>(systems_[type]);
  systems_.erase(type);
}

inline void SystemManager::Update()
{
  for(auto& system : systems_)
  {
    system.second->Update();
  }
}

inline void SystemManager::Init()
{
  for(auto& system : systems_)
  {
      system.second->Init();
  }
}

inline void SystemManager::Exit()
{
  for(auto& system : systems_)
  {
    system.second->Exit();
  }
}

inline SystemManager::SystemManager(World &world) : world_(world) {}

#endif //_SYSTEMMANAGER_H_
