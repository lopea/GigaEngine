//
// Created by javier on 5/5/2020.
//

#include "Mesh.h"

Mesh::Mesh()
{}

Mesh::Mesh(Vertex *verts, unsigned int count)
{
    SetVertices(verts, count);
}

Mesh::Mesh(std::vector<Vertex> &verts) : verts_(verts)
{}

Vertex *Mesh::GetVertices()
{
    if (!verts_.empty())
        return &verts_[0];

    return nullptr;
}

void Mesh::SetVertices(Vertex *array, unsigned int count)
{
    if(count)
    {
        for(int i = 0; i < count ; i++)
        {
            verts_.push_back(array[i]);
        }
    }
}

size_t Mesh::size() const
{
    return verts_.size();
}
