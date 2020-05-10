cmake_minimum_required(VERSION 3.14)

# Project name
project(GigaEngine)

# Setting flags when compiling the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-mavx2")

# Adding all the Directories for linking


# Adding rttr includes as adding them to the subdirectory does nothing

add_subdirectory(lib)
include_directories(lib/glm)

set(Giga_ENGINE_SOURCES
        src/Engine/Component/ComponentTest.h
        src/Engine/Component/ComponentManager.h
        src/Engine/Component/ComponentManager.cpp
        src/Engine/Component/ComponentList.h
        src/Engine/Component/ComponentExceptions.h
        src/Engine/Component/Component.h
        src/Engine/Entity/EntityManager.cpp
        src/Engine/Entity/EntityManager.h
        src/Engine/Entity/EntityList.h
        src/Engine/Entity/EntityList.cpp
        src/Engine/Entity/EntityBase.h
        src/Engine/Entity/EntityBase.cpp
        src/Engine/Entity/Entity.h
        src/Engine/Systems/SystemBase.h
        src/Engine/Systems/SystemBase.cpp
        src/Engine/Engine.cpp src/Engine/Engine.h)

# All the sources for building the Giga Grunts Engine
set(Giga_SOURCES
        src/main.cpp
        src/Graphics.cpp
        src/Graphics.h
        src/Shader.cpp
        src/Shader.h
        src/System.h
        src/Translation.h
        src/Rotation.h
        src/Scale.h
        src/LocalToWorldMatrix.h
        src/Vertex.h
        src/Mesh.cpp
        src/Mesh.h
        src/MatrixSystem.cpp
        src/MatrixSystem.h
        src/Renderer.h
        src/RenderSystem.cpp
        src/RenderSystem.h
        src/Engine/Entity/EntityReferenceList.cpp
        src/Engine/Entity/EntityReferenceList.h
        src/RotateTestSystem.cpp
        src/RotateTestSystem.h src/UniformScale.h)


# Making executable
add_executable(${PROJECT_NAME} ${Giga_ENGINE_SOURCES} ${Giga_SOURCES})

# Linking needed libraries
target_link_libraries(${PROJECT_NAME} glad glfw rttr_core)
