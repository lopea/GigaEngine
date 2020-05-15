add_subdirectory(glad)
add_subdirectory(glfw-3.3.2)
add_subdirectory(glm)

# rttr is a bitch and needs to be pre-compiled (only for windows though)
if(MINGW)
    message("-- Using pre-compiled RTTR for windows...")
    find_library(RTTR_LIBRARY rttr_core rttr-lin/lib)
    set(RTTR_INCLUDES rttr/include)
#Linux will compile on the RTTR source at build time
elseif(UNIX)
    message("-- Using RTTR source for Linux/Unix...")
    add_subdirectory(rttr-lin)
else()
    #lol funny man trying to use MacOS
    message("-- Have Fun! --")
endif()
include_directories(rttr/include)

#add_subdirectory(cereal-master)
#add_subdirectory(imgui-master)