cmake_minimum_required(VERSION 3.5)
project (viewer)

set (CMAKE_CXX_STANDARD 11)

include_directories(./include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(./glfw-3.2.1)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

add_executable(viewer
  src/main.cpp
  src/glad.c
  src/imgui_impl_glfw.cpp
  src/imgui_impl_opengl3.cpp
  src/imgui.cpp
  src/imgui_demo.cpp
  src/imgui_draw.cpp
  src/imgui_widgets.cpp
)

target_link_libraries(viewer glfw)
