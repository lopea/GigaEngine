
#include <iostream>

#include "EngineFiles/Movement.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "EngineFiles/GameObject.h"

static const struct
{
  float x, y;
  float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

const glm::vec3 zAxis(0, 0, 1);

int main(void)
{
  GLFWwindow* window;

  GLuint vertex_buffer, vertex_shader, fragment_shader, program;
  GLint mvp_location, vpos_location, vcol_location;

  /* Initialize the libr1ary */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1080, 1920, "GigaEngine", NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);



  gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  mvp_location = glGetUniformLocation(program, "MVP");
  vpos_location = glGetAttribLocation(program, "vPos");
  vcol_location = glGetAttribLocation(program, "vCol");

  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
    sizeof(vertices[0]), (void*)0);
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertices[0]), (void*)(sizeof(float) * 2));

  GameObject object("Game");
  Movement* movement = object.AddComponent<Movement>();

  movement->GetVelocity() = glm::vec2(1,100);
  std::cout << "Movement: Velocity = " << movement->GetVelocity().x << "," << movement->GetVelocity().y << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      int x, y;
      glm::mat4x4 m, p, mvp;
      float ratio;

      /* Poll for and process events */
      glfwPollEvents();
      glfwGetWindowSize(window, &x, &y);
      glViewport(0, 0, x, y);
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);

      ratio = x / static_cast<float>(y);

      m = glm::identity<glm::mat4x4>();
      m = glm::rotate(m, glm::radians(static_cast<float>(100 * glfwGetTime())), glm::vec3(0.0, 0.0, 1.0));
      p = glm::ortho(ratio, -ratio, -1.0f, 1.0f, -1.0f, 1.0f);
      mvp = p * m;

      glUseProgram(program);
      glad_glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
      glDrawArrays(GL_TRIANGLES, 0, 3);
      
      /* Swap front and back buffers */
      glfwSwapBuffers(window);
    }


  glfwTerminate();
  return EXIT_SUCCESS;
}