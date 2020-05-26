#pragma once

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../Math.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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

// Private Function Declarations:
//-------------------------------
static void checkCompileErrors(unsigned int shader, std::string type);

// Member Functions:
//------------------
inline Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
  SetUp(vertexPath,fragmentPath);
}

inline void Shader::use()
{
  glUseProgram(ID_);
}

inline void Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID_, name.c_str()), int(value));
}

inline void Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID_, name.c_str()), value);
}

inline void Shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID_, name.c_str()), value);
}

inline void Shader::setColor(const std::string &name, float red, float green, float blue) const
{
  glUniform3f(glGetUniformLocation(ID_, name.c_str()), red, green, blue);
}

inline void Shader::setMatrix4x4(const std::string &name, const glm::mat4 &value) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID_,name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
inline void Shader::SetUp(const char* vertexPath, const char* fragmentPath)
{
  if(!vertexPath || !fragmentPath)
    return;

  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  try
  {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode   = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch(std::ifstream::failure& e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  // 2. compile shaders
  unsigned int vertex, fragment;

  // vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);

  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");

  // similiar for Fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(vertex, "FRAGMENT");


  // shader Program
  ID_ = glCreateProgram();
  glAttachShader(ID_, vertex);
  glAttachShader(ID_, fragment);
  glLinkProgram(ID_);
  checkCompileErrors(ID_, "PROGRAM");


  // delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

inline void Shader::Clear()
{
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &VBO_);
  glDeleteProgram(ID_);
}



//Private functions:
//------------------

inline static void checkCompileErrors(unsigned int shader, std::string type)
{
  int success;
  char infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}


#endif //ENGINE_SHADER_H
