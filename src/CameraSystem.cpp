//
// Created by lopea on 6/4/20.
//

#include "CameraSystem.h"
#include "Engine/Entity/EntityManager.h"
#include "Camera.h"
#include "Engine/RenderBounds.h"
#include "MatrixSystem.h"
#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void CameraSystem::Update()
{

  EntityManager::GetEntities().ForEach<Camera, Translation>
          ([](Camera &camera, Translation &translation)
           {
               std::vector<Entity> ents;
               EntityManager::GetEntities().ForEach<RenderBounds, Translation>(
                       [camera, translation, &ents](RenderBounds &bounds, Translation &currPos)
                       {
                           auto pos = currPos.Get();
                           auto cameraPos = translation.Get();
                           if (pos.x + bounds.width / 2 >= cameraPos.x - camera.zoom / 2
                               && cameraPos.x + camera.zoom / 2 >= pos.x - bounds.width / 2
                               && pos.y + bounds.height / 2 >= cameraPos.y - camera.zoom / 2
                               && cameraPos.y + camera.zoom / 2 >= pos.y - bounds.height / 2)
                           {

                             ents.push_back(currPos.GetEntity());
                           }
                       });

               EntityList list = EntityList(ents);

               if (!list.empty())
               {
                 glm::mat4 view = Camera::GenerateViewMatrix(camera, translation);
                 glm::mat4 ortho = Camera::GenerateOrthoMatrix(camera);

                 MatrixSystem::UpdateMatrices(list);

                 list.ForEach<Renderer, LocalToWorldMatrix>
                         ([&view, &ortho](Renderer &renderer, LocalToWorldMatrix &matrix)
                          {
                              //Bind the matrix to the shader
                              glUniformMatrix4fv(glGetUniformLocation(renderer.shader.ID_, "Model"), 1, GL_FALSE,
                                                 glm::value_ptr(matrix.value));

                              glUniformMatrix4fv(glGetUniformLocation(renderer.shader.ID_, "View"), 1, GL_FALSE,
                                                 glm::value_ptr(view));

                              glUniformMatrix4fv(glGetUniformLocation(renderer.shader.ID_, "Projection"), 1, GL_FALSE,
                                                 glm::value_ptr(ortho));

                              //draw the shader
                              glDrawArrays(GL_TRIANGLES, 0, 9);
                          });
               }
           });
}
