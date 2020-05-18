//
// Created by lopea on 5/10/20.
//

#include "Engine.h"
#include "Entity/Entity.h"
#include "Entity/EntityManager.h"
#include "../Translation.h"
#include "../UniformScale.h"
#include "../Renderer.h"
#include "../LocalToWorldMatrix.h"
#include "../MatrixSystem.h"
#include "../RotateTestSystem.h"
#include "../RenderSystem.h"
#include "../Rotation.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool Engine::init_ = false;
Engine Engine::current_;
bool Engine::running_ = false;

void Engine::Initialize()
{
  //Engine is already initialized
  if(init_) { return;}

  if(!glfwInit())
    return;



  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

  //setup the screen
  current_.currentScreen_ = Screen(600, 800, ScreenType::Windowed);
  glfwMakeContextCurrent(current_.currentScreen_.glfwHandle_);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  //setup variables
  init_ = true;
  running_ = true;
}

void Engine::Run()
{
  //creates entities and adds components to them for use in a game
  //TODO: Create Archetypes to avoid doing this every time
  //TODO: Create ArchetypeManager to save all archetypes in a file

  for (int i = 0; i < 5000; i++)
  {
    Entity &ent = EntityManager::AddEntity();
    //ent.AddComponent<ComponentTest>();
    Translation& t = ent.AddComponent<Translation>();
    t.value = glm::vec3(i%100 - 25, i/100 ,  10);
    ent.AddComponent<Rotation>();
    ent.AddComponent<UniformScale>();
    Renderer& rend = ent.AddComponent<Renderer>();
    ent.AddComponent<LocalToWorldMatrix>();
  }

  MatrixSystem m_system;
  RenderSystem r_system;
  RotateTestSystem rot_system;



  //check if the engine is still running
  while(running_)
  {
    if(glfwWindowShouldClose(current_.currentScreen_.GetWindowHandle()))
    {
      running_ = false;
    }
    float timer = glfwGetTime();

    // render
    // ------
    glClearColor(sin(glfwGetTime()), sin(glfwGetTime() * 6), sin(glfwGetTime()* 2), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    rot_system.Update();
    m_system.Update();
    r_system.Update();
    // Shader used to render triangles

    float timeValue = glfwGetTime();
    float greenValue = (sinf(timeValue) / 2.0f) + 0.5f;
    float x = (tanf(timeValue) / 2.0f) + 0.1f;

    //shader.setColor("myColor", 1.0f, greenValue, 0.5f);
    //shader.setFloat("xOffset", x);

    // Used to draw a single triangle

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(Engine::GetScreen().glfwHandle_);
    glfwPollEvents();
    std::cout << 1/(glfwGetTime() - timer) << std::endl; //frame rate
  }
}

Screen Engine::GetScreen()
{
  return current_.currentScreen_;
}
