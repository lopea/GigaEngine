//
// Created by javier on 5/7/2020.
//

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "RotateTestSystem.h"
#include "Engine/Entity/EntityManager.h"
#include "Rotation.h"

void RotateTestSystem::Update()
{
    float time =  glfwGetTime();
    EntityManager::GetEntities().ParallelForEach<Rotation>
            ([time](Rotation& rot)
            {
                rot.value = glm::sin(time) * 10;
            });
}
