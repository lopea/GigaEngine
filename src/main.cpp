#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.h"

int main()
{
    Engine::Initialize();
    Engine::Run();
    return 0;
}
