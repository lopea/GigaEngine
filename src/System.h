#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

#endif //ENGINE_SYSTEM_H

class System
{
public:
  virtual void Init() = 0;
  
  virtual void Update() = 0;
  
  virtual void Shutdown() = 0;
  
};