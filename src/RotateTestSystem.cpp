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
    EntityManager::GetEntities().ParallelForEach
            ([time](Entity& entity)
            {
                Rotation& rot = entity.GetComponent<Rotation>();
                rot.value = glm::sin(time + entity.getID()) * 10;
            });
}
