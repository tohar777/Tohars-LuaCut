#include "CApplication.h"

int CApplication::LCCreateWindow(){
    if(!glfwInit()){
        printf("[GLFW] The GLFW Context Failed");
        return -1;
    }
    glfwWindowHint(GLFW_VERSION_MAJOR,2);
    glfwWindowHint(GLFW_VERSION_MINOR,1);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
    window = glfwCreateWindow(400,500,"Tohars LuaCut",nullptr,nullptr);
    if(!window){
        printf("[GLFW] The GLFW Window Context Failed");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    return 0;
}
void CApplication::LCInitUI(){
    int w,h;
    glfwGetWindowSize(window,&w,&h);
    ui.Init(w,h);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL2_Init();
}
void CApplication::LCRun(){
    LCCreateWindow();
    LCInitUI();
    glClearColor(27.0f/255.0f, 38.0f/255.0f, 89.0f/255.0f,1.0f);
    while(!glfwWindowShouldClose(window)){
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ui.MainMenuBar();
            ui.MainUI();
        }
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}