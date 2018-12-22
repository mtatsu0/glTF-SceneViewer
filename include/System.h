#ifndef SYSTEM_H
#define SYSTEM_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class System
{
 private:
  System();
  ~System();
  
  bool initSuccess = true;
  int scrWidth = 1280;
  int scrHeight = 720;
  static void glfw_error_callback(int error, const char* description);
  
 public:
  System(const System&) = delete;
  System &operator=(const System&) = delete;
  
  static System& Instance();

  GLFWwindow* window;
  
  int mainLoop();
  
  int setScrWidth(int width){ scrWidth = width; }
  int setScrHeight(int height){ scrHeight = height; }
  int getScrWidth(){ return scrWidth; }
  int getScrHeight(){ return scrHeight; }
    
};

void System::glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

System &System::Instance(){
  static System obj;
  return obj;
}
  
System::System() {
  glfwSetErrorCallback(glfw_error_callback);
  
  glfwInit();
    
  const char* glsl_version = "#version 330 core";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(scrWidth, scrHeight, "glTF-SceneViewer", NULL, NULL);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync?
  
  // Initialize OpenGL loader
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  
  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  
}

System::~System() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
}

#endif // SYSTEM_H
