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
    static const float& DeltaTime;
    static const float& CurrentTime;
    static const float& FramesPerSecond;
private:
    static void Update();
    friend class Engine;
};

//Initializers
inline float Time::deltaTime_ = 0;
inline float Time::time_ = 0;
inline float Time::fps_ = 0;
inline float Time::last_ = 0;

//Accessors

/*!
 *  Get the time between this frame and the last one in seconds.
 */
inline const float& Time::DeltaTime = Time::deltaTime_;

/*!
 * Get the time since the application started in seconds.
 */
inline const float& Time::CurrentTime = Time::time_;

/*!
 * Get number of frames per second based on the current delta time.
 */
inline const float& Time::FramesPerSecond = Time::fps_;

/*!
 * Updates time variables.
 * For internal use only. Should only be called once per frame.
 */
inline void Time::Update()
{
    last_ = time_;
    time_ = (float)glfwGetTime();
    deltaTime_ = time_ - last_;
    fps_ = 1/deltaTime_;
}

#endif //GIGAENGINE_TIME_H
