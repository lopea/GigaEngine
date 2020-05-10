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
    float offset = glm::sin(glfwGetTime() * 1) * 2;

    glm::vec3 pos = glm::vec3(offset,0,0);
    glm::mat4 view = glm::lookAt(pos, pos + glm::vec3(0, 0, -1), glm::vec3(0,1,0));
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.f);
    //This code does the following:
    //- Gets all the entities currently used in the game
    //- Goes through each entity and checks if the entity has both a renderer and a local to world matrix
    //- If the current entity has both, execute the following code for the renderer and LTWM pertaining to the entity
    EntityManager::GetEntities().ForEach<Renderer,LocalToWorldMatrix>
            ([view, perspective](Renderer& renderer, LocalToWorldMatrix& matrix)
            {

                //glBindVertexArray(renderer.shader.VBO_);
                glClear(GL_DEPTH_BUFFER_BIT);
                glm::mat4 m =  view * matrix.value ;
                
                //Bind the matrix to the shader
                glUniformMatrix4fv(glGetUniformLocation(renderer.shader.ID_, "MVP"), 1, GL_FALSE, glm::value_ptr(m));

                //draw the shader
                glDrawArrays(GL_TRIANGLES, 0, 9);

            });
}
