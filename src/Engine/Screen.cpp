//
// Created by lopea on 5/16/20.
//

#include "Screen.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"

Screen::Screen(int resX, int resY, ScreenType type)
        : type_(type), resX_(resX), resY_(resX)
{
    //TODO: Add fullscreen
    glfwHandle_ = glfwCreateWindow(resX, resY, "Game", nullptr, nullptr);

    switch (type_)
    {
        case ScreenType::Fullscreen:
            glfwSetWindowMonitor(glfwHandle_, glfwGetPrimaryMonitor(), 0, 0, resX_, resY_, 75);
            break;
        case ScreenType::BorderlessWindowed:
        case ScreenType::Windowed:
            break;
    }

}

GLFWwindow *Screen::GetWindowHandle()
{
    return glfwHandle_;
}

ScreenType Screen::GetScreenType() const
{
    return type_;
}

float Screen::GetRatio() const
{
    return (float) resY_ / resX_;
}

float Screen::GetWidth() const
{
    return resX_;
}

float Screen::GetHeight() const
{
    return resY_;
}

void Screen::ChangeWindowSize(unsigned int newWidth, unsigned int newHeight)
{
    //update resolution values
    resX_ = newWidth;
    resY_ = newHeight;

    glfwSetWindowSize(glfwHandle_, (int) newWidth, (int) newHeight);
}

void Screen::Shutdown()
{
    glfwDestroyWindow(glfwHandle_);
}

