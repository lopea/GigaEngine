//
// Created by javier on 5/5/2020.
//

#ifndef GIGAENGINE_MESH_H
#define GIGAENGINE_MESH_H


#include <vector>
#include "Vertex.h"

class Mesh
{
public:
    Mesh();
    Mesh(Vertex* verts, unsigned int count);
    Mesh(std::vector<Vertex>& verts);
    Vertex* GetVertices();
    void SetVertices(Vertex* array, unsigned int count);
    size_t size() const;

private:
    std::vector<Vertex> verts_;
};


#endif //GIGAENGINE_MESH_H
