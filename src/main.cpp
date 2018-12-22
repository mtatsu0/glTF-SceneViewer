#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
  fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

/*
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
*/

int main()
{
  glfwSetErrorCallback(glfw_error_callback);
  
  if(!glfwInit())
    return 1;

  const char* glsl_version = "#version 330 core";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(1280, 720, "glTF-SceneViewer", NULL, NULL);
  if(window == NULL)
    return 1;

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync
  
  // Initialize OpenGL loader
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.00f, 0.80f, 0.50f, 1.00f);
  
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    // 1. Show the big demo window
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create our selves.
    // ---We use a Begin/End pair to created a named window.
    {
      static float f = 0.0f;
      static int counter = 0;
      
      ImGui::Begin("Hello, world!");

      ImGui::Text("This is some useful text.");
      ImGui::Checkbox("Demo Window", &show_demo_window);
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
      ImGui::ColorEdit3("clear color", (float*)&clear_color);

      if (ImGui::Button("Button"))
	counter++;
      ImGui::SameLine();
      ImGui::Text("conter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.3f FPS)",
		  1000.0f / ImGui::GetIO().Framerate,
		  ImGui::GetIO().Framerate);
                  
      ImGui::End();
      
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
      ImGui::Begin("Another Window", &show_another_window);
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
	show_another_window = false;
      ImGui::End();
    }

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwMakeContextCurrent(window);
    glfwSwapBuffers(window);
  }
  
  //Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}


