//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_MATRIXSYSTEM_H
#define GIGAENGINE_MATRIXSYSTEM_H


#include "Engine/Systems/SystemBase.h"

class EntityList;

class MatrixSystem : public SystemBase
{
public:
    void Update() override;
    static void UpdateMatrices(EntityList& list);
};


#endif //GIGAENGINE_MATRIXSYSTEM_H
