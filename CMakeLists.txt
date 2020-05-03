cmake_minimum_required(VERSION 3.14)

# Project name
project(GigaEngine)

# Setting flags when compiling the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS)

# Adding all the Directories for linking
add_subdirectory(lib)
add_subdirectory(src)

# Making executable
add_executable(${PROJECT_NAME} ${Giga_SOURCES})

# Linking needed libraries
target_link_libraries(${PROJECT_NAME} glad glfw)
