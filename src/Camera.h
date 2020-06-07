//
// Created by javier on 5/22/2020.
//

#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Engine/Component/Component.h"
#include "Engine/Math.h"
#include "Translation.h"

struct Camera : public Component
{
    SET_AS_COMPONENT(Camera)
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 forward = glm::vec3(0.0, 0.0, 1.0);

    float zoom = 10;
    float zNear = -10;
    float zFar = 10;

    static glm::mat4 GenerateOrthoMatrix(Camera& camera)
    {
      return glm::ortho(-camera.zoom/2, camera.zoom/2
              ,-camera.zoom/2, camera.zoom/2,camera.zNear, camera.zFar);

    }
    static glm::mat4 GenerateViewMatrix(const Camera& camera, const Translation& position)
    {
      return glm::lookAt(position.Get(), position.Get() + camera.forward, camera.up);
    }

};

#endif //_CAMERA_H_
