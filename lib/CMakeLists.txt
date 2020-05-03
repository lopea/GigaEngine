add_subdirectory(glad)
add_subdirectory(glfw-3.3.2)
add_subdirectory(glm)

# rttr is a bitch and needs to be pre-compiled
find_library(RTTR_LIBRARY rttr_core rttr/lib)
set(RTTR_INCLUDES  rttr/include)

#add_subdirectory(cereal-master)
#add_subdirectory(imgui-master)