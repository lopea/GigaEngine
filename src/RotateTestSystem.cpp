//
// Created by javier on 5/7/2020.
//

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "RotateTestSystem.h"
#include "Engine/Entity/EntityManager.h"
#include "Engine/Component/Transform/Rotation.h"

void RotateTestSystem::Update()
{
    float time =  glfwGetTime();
    EntityManager::GetEntities().ParallelForEach<Rotation>
            ([time](Rotation& rot)
            {
                rot.Set(glm::sin(time + rot.GetEntity()) * 10);
            });
}
