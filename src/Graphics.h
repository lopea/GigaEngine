#pragma once

#ifndef ENGINE_GRAPHICS_H
#define ENGINE_GRAPHICS_H

#include "GLFW/glfw3.h"
#include "System.h"
#include "Shader.h"


class Graphics
{
public:
  
  explicit Graphics(int Width = 800, int Height = 600, const char* Title = "Working_Project");
  
  void Init();
  
  void Update();
  
  void Close();

private:
  int width_;
  int height_;
  unsigned int VBO_, VAO_, EBO_;
  const char* title_;
  GLFWwindow* window_;
  Shader shader_;
};


#endif //ENGINE_GRAPHICS_H
