#include <iostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
  fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
  printf("width: %d, height: %d\n", width, height);
}

int main()
{
  std::cout << "main() start" << std::endl;
  glfwSetErrorCallback(glfw_error_callback);
  
  if(!glfwInit())
    return 1;
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "glTF-SceneViewer", NULL, NULL);
  if(window == NULL)
    return 1;

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.0f, 0.8f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
  }
  

  glfwDestroyWindow(window);
  glfwTerminate();
  std::cout << "main() end" << std::endl;
  return 0;
}


