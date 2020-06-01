//
// Created by javier on 5/22/2020.
//

#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Engine/Component/Component.h"
#include "Engine/Math.h"

struct Camera : public Component
{
  SET_AS_COMPONENT(Camera)
  glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
  glm::vec3 forward = glm::vec3(0.0, 0.0, -1.0);
  glm::mat4x4 matrix = glm::identity<glm::mat4x4>();
};

#endif //_CAMERA_H_
