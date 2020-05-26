//
// Created by javier on 5/22/2020.
//

#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "../Component.h"
#include "../../Math.h"
class Camera : public Component
{
  SET_AS_COMPONENT(Camera)
  float zoom = 1;
};

#endif //_CAMERA_H_
