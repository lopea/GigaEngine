//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_MATRIXSYSTEM_H
#define GIGAENGINE_MATRIXSYSTEM_H


#include "../SystemBase.h"
#include "../../Transform.h"
#include "../../Entity/EntityManager.h"


class MatrixSystem : public SystemBase
{
public:
    void Update() override;
};

//the axis in which 2D objects will rotate
const glm::vec3 rotateAxis = glm::vec3(0, 0, 1);

//This system will update all the matrices based on the position, rotation, and scale
//each system will update individually as not all entities will contain all these components
inline void MatrixSystem::Update()
{
  //get all entities that need to have their matrices updated
  EntityList updateEntities = EntityManager::GetEntities().OfType<DirtyTransform>();

  //don't do anything if there are no Entites that need to be changed
  if(updateEntities.empty())
    return;

  //Set all matrices to the identity matrix
  updateEntities.ParallelForEach<LocalToWorldMatrix>
          ([](LocalToWorldMatrix &matrix)
           {
               matrix.value = glm::identity<glm::mat4x4>();
           });

  //update the translation of the entity, first
  updateEntities.ParallelForEach<LocalToWorldMatrix, Translation>
          ([](LocalToWorldMatrix &matrix, Translation &trans)
           {
               matrix.value = glm::translate(matrix.value, trans.Get());

           });

  //update the rotation
  updateEntities.ParallelForEach<LocalToWorldMatrix, Rotation>
          ([](LocalToWorldMatrix &matrix, Rotation &rotation)
           {
               matrix.value = glm::rotate(matrix.value,
                                          glm::radians(rotation.Get()),
                                          rotateAxis);
           });

  //update the scale
  updateEntities.ParallelForEach<LocalToWorldMatrix, Scale>
          ([](LocalToWorldMatrix &matrix, Scale &scale)
           {
               matrix.value = glm::scale(matrix.value, scale.Get());
           });


  //update the scale for uniform scales only
  updateEntities.ParallelForEach<LocalToWorldMatrix, UniformScale>
          ([](LocalToWorldMatrix& matrix, UniformScale& scale)
           {
               matrix.value[0].x *= scale.Get();
               matrix.value[1].y *= scale.Get();
               matrix.value[2].z *= scale.Get();

           });


  //remove all DirtyTransform Tags
  ComponentManager::RemoveAllComponents<DirtyTransform>();

}

#endif //GIGAENGINE_MATRIXSYSTEM_H
