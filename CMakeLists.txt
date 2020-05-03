cmake_minimum_required(VERSION 3.14)
project(GigaEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS)

# All the sources for building the Giga Grunts Engine
set(Giga_SOURCES
        src/main.cpp
        src/Graphics.cpp
        src/Graphics.h
        src/Shader.cpp
        src/Shader.h
        src/System.h)

add_subdirectory(lib)
add_subdirectory(src)

add_executable(${PROJECT_NAME} ${Giga_SOURCES})

target_link_libraries(${PROJECT_NAME} glad glfw)
