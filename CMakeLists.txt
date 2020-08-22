cmake_minimum_required(VERSION 3.14)

# Project name
project(GigaEngine)


# Setting flags when compiling the project
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-mavx2 -Wall -Wextra -Wno-unused-parameter -Werror -Wno-implicit-fallthrough -Wno-unknown-pragmas")



if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-Ofast)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_definitions(-Ofast)
endif()

# Adding rttr includes as adding them to the subdirectory does nothing

add_subdirectory(lib)
include_directories(lib/glm)
include_directories(lib/rttr/include)


set(Giga_ENGINE_SOURCES
        src/Engine/Component/ComponentTest.h
        src/Engine/Component/ComponentManager.h
        src/Engine/Component/ComponentList.h
        src/Engine/Component/ComponentExceptions.h
        src/Engine/Component/Component.h
        src/Engine/Entity/EntityManager.cpp
        src/Engine/Entity/EntityManager.h
        src/Engine/Entity/EntityList.h
        src/Engine/Systems/SystemBase.h
        src/Engine/Engine.cpp
        src/Engine/Engine.h
        src/Engine/Math.h
        src/Engine/Screen.cpp
        src/Engine/Screen.h
        src/Engine/Tag/TagBase.h
        src/Engine/Tag/TagManager.h
        src/Engine/Tag/TagList.h
        src/Engine/EventManager.h
        src/Engine/Quadtree.cpp
        src/Engine/Quadtree.h
        src/Engine/RenderBounds.h
        src/CameraSystem.cpp
        src/CameraSystem.h src/Engine/World.cpp src/Engine/World.h)

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
        src/RotateTestSystem.cpp
        src/RotateTestSystem.h src/UniformScale.h src/Camera.cpp src/Camera.h src/Engine/Time.h src/Engine/Systems/SystemManager.cpp src/Engine/Systems/SystemManager.h)





# Making executable
add_executable(${PROJECT_NAME} ${Giga_ENGINE_SOURCES} ${Giga_SOURCES})

# Linking needed libraries
target_link_libraries(${PROJECT_NAME} glad glfw)

if(UNIX)
    # link the correct library
    target_link_libraries(${PROJECT_NAME} rttr_core)
elseif(MINGW)
    #link correct library
    target_link_libraries(${PROJECT_NAME} ${RTTR_LIBRARY})

    #copy correct dll to the project folder
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/lib/rttr/lib/librttr_core.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif()
