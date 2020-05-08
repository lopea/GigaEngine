//
// Created by javier on 5/7/2020.
//

#include <GLFW/glfw3.h>
#include "RotateTestSystem.h"
#include "Engine/Entity/EntityManager.h"
#include "Rotation.h"

void RotateTestSystem::Update()
{
    float time =  glfwGetTime() * 100;
    EntityManager::GetEntities().ForEach<Rotation>
            ([time](Rotation& rot)
            {
                rot.value = time;
            });
}
