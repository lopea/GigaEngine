cmake_minimum_required(VERSION 3.14)

# Project name
project(GigaEngine)

# Setting flags when compiling the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fopenmp")

# All the sources for building the Giga Grunts Engine
set(Giga_SOURCES
        src/main.cpp
        src/Graphics.cpp
        src/Graphics.h
        src/Shader.cpp
        src/Shader.h
        src/System.h
        src/EntityManager.cpp
        src/EntityManager.h
        src/ComponentBase.h
        src/SystemBase.cpp
        src/SystemBase.h
        src/ComponentList.h
        src/EntityBase.cpp
        src/EntityBase.h
        src/ComponentManager.cpp
        src/ComponentManager.h
        src/ComponentTest.h
        src/Entity.h
        src/ComponentExceptions.h src/EntityList.cpp src/EntityList.h)

# Adding all the Directories for linking
add_subdirectory(lib)
add_subdirectory(src)

# Adding rttr includes as adding them to the subdirectory does nothing
include_directories(lib/rttr/include)

# Making executable
add_executable(${PROJECT_NAME} ${Giga_SOURCES})

# Linking needed libraries
target_link_libraries(${PROJECT_NAME} glad glfw ${RTTR_LIBRARY})
