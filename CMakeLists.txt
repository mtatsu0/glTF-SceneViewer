cmake_minimum_required(VERSION 3.5)
project (glTF-SceneViewer)

set (CMAKE_CXX_STANDARD 11)

include_directories(./include)

#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#add_subdirectory(./glfw-3.2.1)

add_executable(viewer
  src/main.cpp
)

#target_link_libraries(ponpokoka glfw)
