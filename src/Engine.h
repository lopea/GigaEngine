//
// Created by lopea on 5/10/20.
//

#ifndef GIGAENGINE_ENGINE_H
#define GIGAENGINE_ENGINE_H


#include "Engine/Screen.h"

class Engine
{
public:
    static void Initialize();
    static Screen GetScreen();

    static void Run();

    static void Terminate();

private:
    Screen currentScreen_;

    static bool running_;
    static bool init_;
    static Engine current_;
};




#endif //GIGAENGINE_ENGINE_H
