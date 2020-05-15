//
// Created by javier on 5/5/2020.
//

#include "RenderSystem.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Engine/Entity/EntityManager.h"
#include "LocalToWorldMatrix.h"
#include "Renderer.h"

void RenderSystem::Update()
{

    //This code does the following:
    //- Gets all the entities currently used in the game
    //- Goes through each entity and checks if the entity has both a renderer and a local to world matrix
    //- If the current entity has both, execute the following code for the renderer and LTWM pertaining to the entity
    EntityManager::GetEntities().ForEach<Renderer,LocalToWorldMatrix>
            ([](Renderer& renderer, LocalToWorldMatrix& matrix)
            {
                //zoom value, scales and translates the object automatically when multiplied in the shader
                matrix.value[3][3] *= 3;

                //Bind the matrix to the shader
                glUniformMatrix4fv(glGetUniformLocation(renderer.shader.ID_, "MVP"), 1, GL_FALSE, glm::value_ptr(matrix.value));

                //draw the shader
                glDrawArrays(GL_TRIANGLES, 0, 9);

            });
}
