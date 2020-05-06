//
// Created by javier on 5/5/2020.
//

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "MatrixSystem.h"
#include "Engine/Entity/EntityManager.h"
#include "LocalToWorldMatrix.h"
#include "Scale.h"
#include "Rotation.h"
#include "Translation.h"

const glm::vec3 rotateAxis = glm::vec3(0, 0, 1);

void MatrixSystem::Update()
{

    //update the scale first
    EntityManager::GetEntities().ForEach<LocalToWorldMatrix, Scale>
            ([](LocalToWorldMatrix &matrix, Scale &scale)
             {
                 matrix.value = glm::identity<glm::mat4x4>();
                 matrix.value = glm::scale(matrix.value, scale.value);
             });

    //update the rotation
    EntityManager::GetEntities().ForEach<LocalToWorldMatrix, Rotation>
            ([](LocalToWorldMatrix &matrix, Rotation &rotation)
             {
                 matrix.value = glm::rotate(matrix.value,
                                            glm::radians(rotation.value),
                                            rotateAxis);
             });

    //update the translation
    EntityManager::GetEntities().ForEach<LocalToWorldMatrix, Translation>
            ([](LocalToWorldMatrix &matrix, Translation &trans)
             {

                 matrix.value = glm::translate(matrix.value, trans.value);
             });
}
