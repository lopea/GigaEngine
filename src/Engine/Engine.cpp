//
// Created by lopea on 5/10/20.
//

#include "Engine.h"
#include "Entity/EntityManager.h"
#include "../Translation.h"
#include "../UniformScale.h"
#include "../Renderer.h"
#include "../LocalToWorldMatrix.h"
#include "../MatrixSystem.h"
#include "../RotateTestSystem.h"
#include "../RenderSystem.h"
#include "../Rotation.h"
#include "EventManager.h"
#include "../Camera.h"
#include "../CameraSystem.h"
#include "RenderBounds.h"
#include "Time.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool Engine::init_ = false;
Engine Engine::current_;
bool Engine::running_ = false;

Shader shader_;

void Engine::Initialize()
{
    //Engine is already initialized
    if (init_)
    { return; }

    //glfw could not initialize
    if (!glfwInit())
        return;


    //set shit up
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, false);

    //setup the screen
    current_.currentScreen_ = Screen(1280, 720, ScreenType::Windowed);
    glfwMakeContextCurrent(current_.currentScreen_.glfwHandle_);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    //setup variables
    init_ = true;
    running_ = true;

    //initialize managers
    ComponentManager::Initialize();
    EntityManager::Initialize();

    shader_ = Shader("../src/Shaders/shader.vs", "../src/Shaders/shader.fs");

    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
    };

    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    // Initializing all buffers
    //-------------------------
    glGenVertexArrays(1, &shader_.VAO_);
    glGenBuffers(1, &shader_.VBO_);
    glGenBuffers(1, &shader_.EBO_);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(shader_.VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, shader_.VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shader_.EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glUseProgram(shader_.ID_);
}

void Engine::Run()
{
    //creates entities and adds components to them for use in a game
    //TODO: Create Archetypes to avoid doing this every time
    //TODO: Create ArchetypeManager to save all archetypes in a file



    for (int i = 0; i < 1000; i++)
    {
        Entity ent = EntityManager::AddEntity();
        //ent.AddComponent<ComponentTest>();
        Translation *t = ComponentManager::AddComponent<Translation>(ent);
        t->Set(glm::vec3(i % 100 - 25, i / 100, i/500.0f));
        ComponentManager::AddComponent<Rotation>(ent);
        ComponentManager::AddComponent<UniformScale>(ent);
        Renderer *rend = ComponentManager::AddComponent<Renderer>(ent);
        rend->shader = shader_;
        ComponentManager::AddComponent<LocalToWorldMatrix>(ent);
        ComponentManager::AddComponent<RenderBounds>(ent);
    }

    Entity ent = EntityManager::AddEntity();
    Translation* tr = ComponentManager::AddComponent<Translation>(ent);

    Camera* camera = ComponentManager::AddComponent<Camera>(ent);

    RotateTestSystem rot_system;
    CameraSystem c_system;

    bool check = false;

    //check if the engine is still running
    while (running_)
    {
        if (glfwWindowShouldClose(GetScreen().GetWindowHandle()))
        {
            running_ = false;
            Engine::Terminate();
        }

        Time::Update();
        EntityManager::CheckForDestruction();

        if(glfwGetKey(GetScreen().GetWindowHandle(),GLFW_KEY_D))
        {
          glm::vec3 pos = tr->Get();
          pos.x -= 100 * Time::DeltaTime;
          tr->Set(pos);
        }
      if(glfwGetKey(GetScreen().GetWindowHandle(),GLFW_KEY_W))
      {
        if(camera->zoom < 0)
          camera->zoom = 0;

        camera->zoom -= 100 * Time::DeltaTime;
      }
        if(glfwGetKey(GetScreen().GetWindowHandle(),GLFW_KEY_A))
        {
          glm::vec3 pos = tr->Get();
          pos.x += 100 * Time::DeltaTime;
          tr->Set(pos);
        }
        if(glfwGetKey(GetScreen().GetWindowHandle(),GLFW_KEY_S))
        {
          camera->zoom += 100 * Time::DeltaTime;
        }
        // render
        // ------
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        rot_system.Update();
        c_system.Update();
        glfwSwapBuffers(Engine::GetScreen().GetWindowHandle());
        glfwPollEvents();

        if (abs(fmod(glfwGetTime(), 0.5)) < 0.02)
        {
            std::string s = "Fps: ";
            s += std::to_string((int)(Time::FramesPerSecond));
            glfwSetWindowTitle(GetScreen().GetWindowHandle(), s.c_str());
        }
        if(Time::CurrentTime > 5  && Time::CurrentTime < 10 && !check)
        {
            for(int i = 0; i < 500; i ++)
            {
                EntityManager::DestroyEntity(i);
            }
            check = true;
        }
        if(Time::CurrentTime > 10 && check)
        {
            for (int i = 0; i < 500; i++)
            {
                Entity e = EntityManager::AddEntity();
                //e.AddComponent<ComponentTest>();
                Translation *t = ComponentManager::AddComponent<Translation>(e);
                t->Set(glm::vec3(i % 100 - 25, i / 100, i/500.0f));
                ComponentManager::AddComponent<Rotation>(e);
                ComponentManager::AddComponent<UniformScale>(e);
                Renderer *rend = ComponentManager::AddComponent<Renderer>(e);
                rend->shader = shader_;
                ComponentManager::AddComponent<LocalToWorldMatrix>(e);
                ComponentManager::AddComponent<RenderBounds>(e);
            }
            check = false;
        }

    }
}

/*!
 * Get the handle that represents the main screen in the game.
 * @return the handle to the main screen
 */
Screen Engine::GetScreen()
{
    return current_.currentScreen_;
}

void Engine::Terminate()
{
#pragma omp critical
  {
    running_ = false;
    init_ = false;
    ComponentManager::Shutdown();
    EntityManager::Shutdown();
    GetScreen().Shutdown();
    glfwTerminate();
    exit(EXIT_SUCCESS);
  }
}
