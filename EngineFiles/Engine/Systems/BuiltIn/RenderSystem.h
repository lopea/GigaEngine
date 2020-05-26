//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_RENDERSYSTEM_H
#define GIGAENGINE_RENDERSYSTEM_H


#include "../SystemBase.h"
#include "../../Math.h"
#include "../../Entity/EntityManager.h"
#include "../../Transform.h"
#include "../../Component/Rendering/Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class RenderSystem : public SystemBase
{
public:
    void Update() override;
};

inline void RenderSystem::Update()
{

  //This code does the following:
  //- Gets all the entities currently used in the game
  //- Goes through each entity and checks if the entity has both a renderer and a local to world matrix
  //- If the current entity has both, execute the following code for the renderer and LTWM pertaining to the entity
  EntityManager::GetEntities().ForEach<Renderer, LocalToWorldMatrix>
          ([](Renderer &renderer, LocalToWorldMatrix &matrix)
           {

               matrix.value[3][3] = 100;

               //Bind the matrix to the shader
               glUniformMatrix4fv(glGetUniformLocation(renderer.shader.ID_, "MVP"), 1, GL_FALSE,
                                  glm::value_ptr(matrix.value));

               //draw the shader
               glDrawArrays(GL_TRIANGLES, 0, 9);
           });
}

#endif //GIGAENGINE_RENDERSYSTEM_H
