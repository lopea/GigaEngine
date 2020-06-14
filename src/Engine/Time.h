//
// Created by lopea on 6/12/20.
//

#ifndef GIGAENGINE_TIME_H
#define GIGAENGINE_TIME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Time
{
private:
    static float deltaTime_;
    static float time_;
    static float fps_;
    static float last_;
public:
    static const float& deltaTime;
    static const float& time;
    static const float& fps;
private:
    static void Update();
    friend class Engine;
};

//Initializers
inline float Time::deltaTime_ = 0;
inline float Time::time_ = 0;
inline float Time::fps_ = 0;
inline float Time::last_ = 0;
inline const float& Time::deltaTime = Time::deltaTime_;
inline const float& Time::time = Time::time_;
inline const float& Time::fps = Time::fps_;

inline void Time::Update()
{
    last_ = time_;
    time_ = (float)glfwGetTime();
    deltaTime_ = time_ - last_;
    fps_ = 1/deltaTime_;
}

#endif //GIGAENGINE_TIME_H
