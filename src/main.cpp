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
      // current directory path
      static boost::filesystem::path p(".");
      // path history
      static std::vector<boost::filesystem::path> pHisUndo{p};
      static std::vector<boost::filesystem::path> pHisRedo;
      // selected file(not a directory) would be highlighted
      static boost::filesystem::path selectedFile("");
      
      // create window
      ImGui::Begin("mywindow");

      // Buttons for traverse directory.
      float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
      ImGui::PushButtonRepeat(true);
      // Undo
      if (ImGui::ArrowButton("##left", ImGuiDir_Left))
	{
	  if(pHisUndo.size() > 1){
	    selectedFile.clear();
	    pHisRedo.push_back(pHisUndo.back());
	    pHisUndo.pop_back();
	    p = pHisUndo.back();
	  }
      }
      ImGui::SameLine(0.0f, spacing);
      // Redo
      if (ImGui::ArrowButton("##right", ImGuiDir_Right))
	{
	  if(pHisRedo.size() > 0){
	    selectedFile.clear();
	    pHisUndo.push_back(pHisRedo.back());
	    pHisRedo.pop_back();
	    p = pHisUndo.back();
	  }
      }
      ImGui::PopButtonRepeat();
      ImGui::SameLine(0.0f, spacing);
      boost::filesystem::path tmp_p = p;
      ImGui::Text(boost::filesystem::canonical(tmp_p/=selectedFile.filename()).c_str());

      // Child Window
      ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
      ImGui::BeginChild("Child1", ImVec2(ImGui::GetWindowContentRegionWidth(), 200), false, window_flags);
      if (boost::filesystem::exists(p))
	{
	  if (boost::filesystem::is_directory(p))
	    {	
	      std::vector<boost::filesystem::path> files;

	      for (auto&& entry : boost::filesystem::directory_iterator(p))
		files.push_back(entry.path());

	      std::sort(files.begin(), files.end());

	      
	      for (auto&& file : files){
		
		if (boost::filesystem::is_directory(file))
		  {
		    // directory has colored text
		    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
		    ImGui::Selectable(file.filename().c_str());
		    ImGui::PopStyleColor();
		    // change directory
		    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
		      {
			selectedFile.clear();
			// clear pathHistoryRedo
			pHisRedo.clear();
			pHisRedo.shrink_to_fit();
			// change current directory
			p = file;
			pHisUndo.push_back(file);
		      }
		  }
		else
		  {
		    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
		    if(ImGui::Selectable(file.filename().c_str(), selectedFile==file))
		      {
			// selected file would be highlighted.
			std::cout << file.filename().c_str() << std::endl;
			selectedFile = file;
		      }
		    ImGui::PopStyleColor();
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
      
      ImGui::EndChild();

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


