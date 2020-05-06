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
    EntityManager::GetEntities().ForEach<Renderer,LocalToWorldMatrix>
            ([](Renderer& renderer, LocalToWorldMatrix& matrix)
            {
                renderer.shader.use();
                glUniformMatrix4fv(renderer.shader.matrix_location,
                                   1, GL_FALSE,
                                   glm::value_ptr(matrix.value));
                glBindVertexArray(renderer.shader.VBO_);
                glDrawArrays(GL_TRIANGLES, 0, 9);

                glBindVertexArray(renderer.shader.VAO_);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.shader.EBO_);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            });
}
