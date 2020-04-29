cmake_minimum_required(VERSION 3.16)
project(GigaEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)


include_directories(lib/glfw/include)
include_directories(lib/glm)
include_directories(include)

add_executable(GigaEngine main.cpp src/glad.c )

target_link_libraries(GigaEngine glfw opengl32 ${GLFW_LIBRARIES})

