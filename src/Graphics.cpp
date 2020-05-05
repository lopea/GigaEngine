
#include <iostream>
#include <cmath>
#include <thread>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Graphics.h"
#include "ComponentTest.h"
#include "EntityManager.h"
#include "Entity.h"

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
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

void Graphics::Update()
{
    // render loop
    // -----------
    for(int i = 0; i < 5000; i++)
    {
        Entity ent = EntityManager::AddEntity();
        ent.AddComponent<ComponentTest>();
    }

    while (!glfwWindowShouldClose(window_))
    {
        double start = glfwGetTime();
        EntityManager::GetEntities().ForEach<ComponentTest>([] (ComponentTest& test)
        {
            test.value = glfwGetTime();
        });
        // input
        // -----
        processInput(window_);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Shader used to render triangles
        shader_.use();
        float timeValue = glfwGetTime();
        float greenValue = (sinf(timeValue) / 2.0f) + 0.5f;
        float x = (tanf(timeValue) / 2.0f) + 0.1f;

        //shader_.setColor("myColor", 1.0f, greenValue, 0.5f);
        //shader_.setFloat("xOffset", x);

        // Used to draw a single triangle
        glBindVertexArray(VBO_);
        glDrawArrays(GL_TRIANGLES, 0, 9);

        // Used to draw many rectangles (AKA, two triangles together).
        glBindVertexArray(VAO_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window_);
        glfwPollEvents();
        std::cout << 1 / (glfwGetTime() - start) << std::endl;
    }
}

void Graphics::Close()
{
    // de-allocate all resources once they've outlived their purpose:
    // --------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteProgram(shader_.ID_);

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
