//
// Created by lopea on 5/16/20.
//

#ifndef GIGAENGINE_SCREEN_H
#define GIGAENGINE_SCREEN_H

#include <GLFW/glfw3.h>


class Screen
{
    bool ShouldClose();

    void Close();

    GLFWwindow *GetWindowHandle();


private:
    GLFWwindow *glfwHandle;
};


#endif //GIGAENGINE_SCREEN_H
