cmake_minimum_required(VERSION 3.14)

# Project name
project(GigaEngine)

# Setting flags when compiling the project
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-mavx2 ")



if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-Ofast)
endif()

# Adding rttr includes as adding them to the subdirectory does nothing

add_subdirectory(lib)
include_directories(lib/glm)
include_directories(lib/rttr/include)
include_directories(EngineFiles)



# All the sources for building the Giga Grunts Engine
set(Giga_SOURCES
        src/main.cpp
        src/Graphics.cpp
        src/Graphics.h
        src/System.h
        src/RotateTestSystem.cpp
        src/RotateTestSystem.h
        src/Engine.cpp
        src/Engine.h)





# Making executable
add_executable(${PROJECT_NAME} ${Giga_ENGINE_SOURCES} ${Giga_SOURCES})

# Linking needed libraries
target_link_libraries(${PROJECT_NAME} glad glfw)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} rttr_core)
elseif(MINGW)
    target_link_libraries(${PROJECT_NAME} ${RTTR_LIBRARY})
endif()
