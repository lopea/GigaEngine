#pragma once

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Engine/Math.h"

class Shader
{
public:
  // the program ID
  unsigned int ID_;
  unsigned int VBO_;
  unsigned int VAO_;
  unsigned int EBO_;

  bool setup;

  // constructor reads and builds the shader
  Shader() = default;
  Shader(const char* vertexPath, const char* fragmentPath);

  // use/activate the shader
  void use();
  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setColor(const std::string &name, float red, float green, float blue) const;
  void setMatrix4x4(const std::string &name,const glm::mat4 &value) const;
  void SetUp(const char* vertexPath, const char* fragmentPath);
  void Clear();
};

#endif //ENGINE_SHADER_H
