#include "CApplication.h"
#include "CSplash.h"

int CApplication::LCCreateWindow()
{
    if (!glfwInit())
    {
        printf("[GLFW] The GLFW Context Failed");
        return -1;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(
        800,
        480,
        "Tohars LuaCut",
        nullptr,
        nullptr
    );

    if (!window)
    {
        printf("[GLFW] The GLFW Window Context Failed");
        glfwTerminate();
        return -1;
    }
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    if(monitor)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        int windowWidth = 500;
        int windowHeight = 270;

        int x = (mode->width - windowWidth) / 2;
        int y = (mode->height - windowHeight) / 2;

        glfwSetWindowPos(window, x, y);
    }
    glfwMakeContextCurrent(window);

    return 0;
}

void CApplication::LCInitUI()
{
    int w, h;

    glfwGetWindowSize(window, &w, &h);

    ui.Init(w, h);

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();
}

void CApplication::LCRun()
{
    // Show splash first
    CSplash splash;
    splash.LCRun();

    // Create the actual application window
    if (LCCreateWindow() != 0)
        return;

    LCInitUI();

    glClearColor(27.0f / 255.0f,38.0f / 255.0f,89.0f / 255.0f,1.0f);

    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ui.MainMenuBar();
        ui.MainUI();
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}