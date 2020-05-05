#include "Graphics.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ComponentTest.h"
#include <rttr/type>

int main()
{
    Graphics openGl;
    EntityManager::Initialize();


    openGl.Init();


    openGl.Update();

    openGl.Close();

    return 0;
}