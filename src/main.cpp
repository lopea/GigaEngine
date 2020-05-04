#include "Graphics.h"
#include "EntityComponents.h"
#include "EntityManager.h"
#include "ComponentTest.h"
#include <rttr/type>
int main()
{
  Graphics openGl;
  EntityManager::Initialize();
  Entity ent = EntityManager::AddEntity();

  ComponentTest& t = ent.AddComponent<ComponentTest>();
  t.value = 4;
  ComponentTest y;
  ent.GetComponent(y);
  std::cout << y.value << std::endl;
  openGl.Init();
  
  openGl.Update();
  
  openGl.Close();
  
  return 0;
}