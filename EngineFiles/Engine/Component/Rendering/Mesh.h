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

inline Mesh::Mesh()
{}

inline Mesh::Mesh(Vertex *verts, unsigned int count)
{
  SetVertices(verts, count);
}

inline Mesh::Mesh(std::vector<Vertex> &verts) : verts_(verts)
{}

inline Vertex *Mesh::GetVertices()
{
  if (!verts_.empty())
    return &verts_[0];

  return nullptr;
}

inline void Mesh::SetVertices(Vertex *array, unsigned int count)
{
  if(count)
  {
    for(int i = 0; i < count ; i++)
    {
      verts_.push_back(array[i]);
    }
  }
}

inline size_t Mesh::size() const
{
  return verts_.size();
}


#endif //GIGAENGINE_MESH_H
