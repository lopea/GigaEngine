
#include <iostream>
#include <cmath>
#include <thread>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Graphics.h"
#include "Engine/Entity/EntityManager.h"
#include "Engine/Component/ComponentTest.h"
#include "Renderer.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"
#include "LocalToWorldMatrix.h"
#include "MatrixSystem.h"
#include "RenderSystem.h"
#include "RotateTestSystem.h"
#include "UniformScale.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);


Graphics::Graphics(int Width, int Height, const char *Title) : width_(Width), height_(Height), VBO_(0), VAO_(0),
                                                               EBO_(0), title_(Title), window_(nullptr),
                                                               shader_(nullptr, nullptr)
{
}

void Graphics::Init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    // Only need if using MacOS
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
    if (!window_)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }



}

void Graphics::Update()
{
    //creates entities and adds components to them for use in a game
    //TODO: Create Archetypes to avoid doing this every time
    //TODO: Create ArchetypeManager to save all archetypes in a file


    MatrixSystem m_system;
    RenderSystem r_system;
    RotateTestSystem rot_system;


    while (!glfwWindowShouldClose(window_))
    {

        // input
        // -----
        processInput(window_);
        float timer = glfwGetTime();

        // render
        // ------
        glClearColor(sin(glfwGetTime()), sin(glfwGetTime() * 6), sin(glfwGetTime()* 2), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //rot_system.Update();
        //m_system.Update();
        //r_system.Update();
        // Shader used to render triangles

        //float timeValue = glfwGetTime();
        //float greenValue = (sinf(timeValue) / 2.0f) + 0.5f;
        //float x = (tanf(timeValue) / 2.0f) + 0.1f;

        //shader.setColor("myColor", 1.0f, greenValue, 0.5f);
        //shader.setFloat("xOffset", x);

        // Used to draw a single triangle
        shader_.use();

        glBindVertexArray(shader_.VBO_);
        glDrawArrays(GL_TRIANGLES, 0, 9);

        glBindVertexArray(shader_.VAO_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shader_.EBO_);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window_);
        glfwPollEvents();
        std::cout << 1/(glfwGetTime() - timer) << std::endl; //frame rate
    }
}

void Graphics::Close()
{
    // de-allocate all resources once they've outlived their purpose:
    // --------------------------------------------------------------
    shader_.Clear();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    // Close the context and close the program
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Show triangles as lines
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Show triangles normally
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}
