//
// Created by lopea on 6/4/20.
//

#ifndef GIGAENGINE_QUADTREE_H
#define GIGAENGINE_QUADTREE_H

#include <array>
#include "Math.h"
#include "Entity/EntityManager.h"

typedef uint64_t Entity;

class Box
{
    Box(float x, float y, float width, float height) : values_(x,y,width,height){}
    bool isColliding(glm::vec2 value) const {return
                                                value.x > values_.x - values_.z/2
                                             && value.x < values_.x + values_.z/2
                                             && value.y > values_.y - values_.w/2
                                             && value.y < values_.y + values_.w/2;}

    bool isColliding(float x, float y) const {return isColliding(glm::vec2(x,y));}

private:
    glm::vec4 values_;
};

class Quadtree
{
public:
    Quadtree(float posX, float posY, float width, float height);
private:
    struct Node
    {
        std::array<Node*, 4> children;
        Box bounds;
        glm::vec2 position;
        Entity entity;
        bool isLeaf;
        Node(glm::vec2 pos, Box box);
        void Split();
        int GetIndex(glm::vec2 pos);
        
    };

    Node* root_;

};


#endif //GIGAENGINE_QUADTREE_H
