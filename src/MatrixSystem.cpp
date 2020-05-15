//
// Created by javier on 5/5/2020.
//

#include "Engine/Math.h"
#include <GLFW/glfw3.h>
#include "MatrixSystem.h"
#include "Engine/Entity/EntityManager.h"
#include "LocalToWorldMatrix.h"
#include "Scale.h"
#include "Rotation.h"
#include "Translation.h"
#include "UniformScale.h"

//the axis in which 2D objects will rotate
const glm::vec3 rotateAxis = glm::vec3(0, 0, 1);

//This system will update all the matrices based on the position, rotation, and scale
//each system will update individually as not all entities will contain all these components

//FIXME: This is ultra inefficient, all the matrices get updated regardless of movement

void MatrixSystem::Update()
{
    //Set all matrices to the identity matrix
    EntityManager::GetEntities().ParallelForEach<LocalToWorldMatrix>
            ([](LocalToWorldMatrix &matrix)
             {
                 matrix.value = glm::identity<glm::mat4x4>();

             });

    //update the translation of the entity, first
    EntityManager::GetEntities().ParallelForEach<LocalToWorldMatrix, Translation>
            ([](LocalToWorldMatrix &matrix, Translation &trans)
             {
                 matrix.value = glm::translate(matrix.value, trans.value);

             });

    //update the rotation
    EntityManager::GetEntities().ParallelForEach<LocalToWorldMatrix, Rotation>
            ([](LocalToWorldMatrix &matrix, Rotation &rotation)
             {
                 matrix.value = glm::rotate(matrix.value,
                                            glm::radians(rotation.value),
                                            rotateAxis);
             });

    //update the scale
    EntityManager::GetEntities().ParallelForEach<LocalToWorldMatrix, Scale>
            ([](LocalToWorldMatrix &matrix, Scale &scale)
             {
                 matrix.value = glm::scale(matrix.value, scale.value);
             });


    //update the scale for uniform scales only
    EntityManager::GetEntities().ParallelForEach<LocalToWorldMatrix, UniformScale>
            ([](LocalToWorldMatrix& matrix, UniformScale& scale)
            {
                matrix.value[0].x *= scale.value;
                matrix.value[1].y *= scale.value;
                matrix.value[2].z *= scale.value;

            });

}
