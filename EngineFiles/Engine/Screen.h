//
// Created by Javier on 5/16/20.
//

#ifndef GIGAENGINE_SCREEN_H
#define GIGAENGINE_SCREEN_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>


enum class ScreenType
{
    Windowed,
    Fullscreen,
    BorderlessWindowed
};

class Screen
{
    GLFWwindow *GetWindowHandle();

    ScreenType GetScreenType() const;

    float GetWidth() const;

    float GetHeight() const;

    void ChangeWindowSize(unsigned int newWidth, unsigned int newHeight);

    float ChangeWindowType(const ScreenType type);

    float GetRatio() const;



private:
    friend class Engine;

    GLFWwindow *glfwHandle_;
    ScreenType type_;
    unsigned int resX_;
    unsigned int resY_;

    Screen(int resX, int resY, ScreenType type);
    Screen() = default;
    float OnWindow(GLFWwindow* window, int width, int height);
    void Shutdown();
};

inline Screen::Screen(int resX, int resY, ScreenType type) : resX_(resX), resY_(resY), type_(type)
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

inline GLFWwindow *Screen::GetWindowHandle()
{
  return glfwHandle_;
}

inline ScreenType Screen::GetScreenType() const
{
  return type_;
}

inline float Screen::GetRatio() const
{
  return (float)resY_/resX_;
}

inline float Screen::GetWidth() const
{
  return resX_;
}

inline float Screen::GetHeight() const
{
  return resY_;
}

inline void Screen::ChangeWindowSize(unsigned int newWidth, unsigned int newHeight)
{
  //update resolution values
  resX_ = newWidth;
  resY_ = newHeight;

  glfwSetWindowSize(glfwHandle_, (int)newWidth, (int)newHeight);
}

inline void Screen::Shutdown()
{
  glfwDestroyWindow(glfwHandle_);
}

#endif //GIGAENGINE_SCREEN_H
