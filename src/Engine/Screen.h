//
// Created by Javier on 5/16/20.
//

#ifndef GIGAENGINE_SCREEN_H
#define GIGAENGINE_SCREEN_H


typedef struct GLFWwindow GLFWwindow;

enum class ScreenType
{
    Windowed,
    Fullscreen,
    BorderlessWindowed
};

class Screen
{
    GLFWwindow *GetWindowHandle();

    ScreenType GetScreenType() const;

    float GetWidth() const;

    float GetHeight() const;

    void ChangeWindowSize(unsigned int newWidth, unsigned int newHeight);

    float ChangeWindowType(const ScreenType type);

    float GetRatio() const;


private:
    friend class Engine;

    GLFWwindow *glfwHandle_;
    ScreenType type_;
    unsigned int resX_;
    unsigned int resY_;

    Screen(int resX, int resY, ScreenType type);
    Screen() = default;
    float OnWindow(GLFWwindow* window, int width, int height);
};


#endif //GIGAENGINE_SCREEN_H
