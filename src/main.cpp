#include <iostream>
#include <stdio.h>

#include "System.h"
/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>
*/


/*
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
*/

int main()
{
  
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.00f, 0.80f, 0.50f, 1.00f);
  
  while(!glfwWindowShouldClose(System::Instance().window)) {
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    // 1. Show the big demo window
    // ImGui::ShowDemoWindow() is in imgui_demo.cpp
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

    // 4. Show a simple window that display files.
    {
      boost::filesystem::path p(".");
            
      ImGui::Begin("mywindow");

      if (boost::filesystem::exists(p))
	{
	  if (boost::filesystem::is_directory(p))
	    {
	      std::vector<boost::filesystem::path> v;

	      for (auto&& x : boost::filesystem::directory_iterator(p))
		v.push_back(x.path());

	      std::sort(v.begin(), v.end());

	      for (auto&& x : v){
		if (boost::filesystem::is_directory(x.filename()))
		  {
		    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), x.filename().c_str());
		  }
		else
		  {
		    ImGui::Text(x.filename().c_str());
		  }
	      }
		
	    }
	  else {
	    ImGui::Text("not a directory");
	  }
	}
      else {
	for (int i = 0; i < 3; i++)
	{
	  ImGui::Text("hey");
	}
      }
      
      
      ImGui::End();
      
    }
    
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwMakeContextCurrent(System::Instance().window);
    glfwGetFramebufferSize(System::Instance().window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwMakeContextCurrent(System::Instance().window);
    glfwSwapBuffers(System::Instance().window);
  }
  
  //Cleanup
  
  return 0;
}


