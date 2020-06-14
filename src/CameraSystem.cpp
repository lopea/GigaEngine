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
               //store all entities in the camera's sight
               EntityList list;

               //Go through each list with a render bounds and a translation component
               EntityManager::GetEntities().ForEach<RenderBounds, Translation>(
                       [camera, translation, &list](RenderBounds &bounds, Translation &currPos)
                       {
                           //get the position of the current entity
                           auto pos = currPos.Get();

                           //get the current camera position
                           auto cameraPos = translation.Get();

                           //check if the camera is looking at the current entity
                           if (pos.x + bounds.width / 2 >= cameraPos.x - camera.zoom / 2
                               && cameraPos.x + camera.zoom / 2 >= pos.x - bounds.width / 2
                               && pos.y + bounds.height / 2 >= cameraPos.y - camera.zoom / 2
                               && cameraPos.y + camera.zoom / 2 >= pos.y - bounds.height / 2)
                           {
                             //Add it to the list if it is
                             list.Add(currPos.GetEntity());
                           }
                       });

               //if the list is not empty,
               if (!list.empty())
               {
                 //Get View Matrix
                 glm::mat4 view = Camera::GenerateViewMatrix(camera, translation);
                 //Get Perspective Matrix
                 glm::mat4 ortho = Camera::GenerateOrthoMatrix(camera);

                 //Update all Model Matrices for each entity that is in the list
                 MatrixSystem::UpdateMatrices(list);

                 //Render All entities in the camera's view.
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
