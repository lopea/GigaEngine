cmake_minimum_required(VERSION 3.14)
project(GigaEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS)

add_subdirectory(lib)
add_subdirectory(src)

add_executable(${PROJECT_NAME} ${GigaGrunts_SOURCES})

target_link_libraries(${PROJECT_NAME} glad glfw)
