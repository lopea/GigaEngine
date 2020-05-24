//
// Created by lopea on 5/16/20.
//

#include "Screen.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"

Screen::Screen(int resX, int resY, ScreenType type) : resX_(resX), resY_(resY), type_(type)
{
  //TODO: Add fullscreen
  glfwHandle_ = glfwCreateWindow(resX,resY,"Game", nullptr, nullptr);

  switch (type_)
  {
    case ScreenType::Fullscreen:
      glfwSetWindowMonitor(glfwHandle_,glfwGetPrimaryMonitor(), 0,0, resX_, resY_, 75);
      break;
  }

}

GLFWwindow *Screen::GetWindowHandle()
{
  return glfwHandle_;
}

ScreenType Screen::GetScreenType() const
{
  return type_;
}

float Screen::GetRatio() const
{
  return (float)resY_/resX_;
}

float Screen::GetWidth() const
{
  return resX_;
}

float Screen::GetHeight() const
{
  return resY_;
}


