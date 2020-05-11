cmake_minimum_required(VERSION 3.14)

project(glad)

add_library(glad INTERFACE)
target_sources(glad INTERFACE src/glad.c)
target_include_directories(glad INTERFACE include/)

if(UNIX)
  target_link_libraries(glad INTERFACE dl)
endif()