
#include <iostream>
#include <cmath>
#include "Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Private Function Declarations:
//-------------------------------
void checkCompileErrors(unsigned int shader, std::string type);

// Member Functions:
//------------------
Shader::Shader(const char *vertexPath, const char *fragmentPath)
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
  catch(std::ifstream::failure e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
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

void Shader::use()
{
  glUseProgram(ID_);
}

void Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID_, name.c_str()), int(value));
}

void Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID_, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID_, name.c_str()), value);
}

void Shader::setColor(const std::string &name, float red, float green, float blue) const
{
  glUniform3f(glGetUniformLocation(ID_, name.c_str()), red, green, blue);
}

//Private functions:
//------------------

void checkCompileErrors(unsigned int shader, std::string type)
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