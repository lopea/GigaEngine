cmake_minimum_required(VERSION 3.14)
project(GigaEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS)

add_subdirectory(lib)
add_subdirectory(include)

add_executable(${PROJECT_NAME} main.cpp src/glad.c )

target_link_libraries(${PROJECT_NAME} glfw opengl32 ${GLFW_LIBRARIES})



target_link_libraries(${PROJECT_NAME} glad glfw)