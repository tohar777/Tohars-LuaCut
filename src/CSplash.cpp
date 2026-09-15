#define STB_IMAGE_IMPLEMENTATION
#include "CSplash.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <stb/stb_image.h>

int CSplash::LCCreateWindow(){

    if(!glfwInit()){

        printf("[GLFW] The GLFW Context Failed");
        return -1;

    }

    glfwWindowHint(GLFW_VERSION_MAJOR,2);
    glfwWindowHint(GLFW_VERSION_MINOR,1);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED,GLFW_FALSE);

    window = glfwCreateWindow(
        500,
        270,
        "Tohars LuaCut- Splash",
        nullptr,
        nullptr
    );

    if(!window){

        printf("[GLFW] The GLFW Window Context Failed");
        glfwTerminate();
        return -1;

    }

    // Center splash window
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("[GLAD] Failed to initialize GLAD\n");
        return -1;
    }

    return 0;
}
GLuint ImageLoader(const char* path)
{
    int width;
    int height;
    int channels;

    unsigned char* data = stbi_load(
        path,
        &width,
        &height,
        &channels,
        4
    );

    if (!data)
        return 0;

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP_TO_EDGE
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP_TO_EDGE
    );

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return texture;
}
void CSplash::LCInitUI(){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL2_Init();
}

void CSplash::LCRun(){

    LCCreateWindow();

    LCInitUI();

    GLuint logo = ImageLoader("splash.png");

    glClearColor(
        27.0f/255.0f,
        38.0f/255.0f,
        89.0f/255.0f,
        1.0f
    );

    auto start = std::chrono::steady_clock::now();
    int w,h;
    glfwGetWindowSize(window,&w,&h);
    while(!glfwWindowShouldClose(window)){

        auto now = std::chrono::steady_clock::now();

        float elapsed =
            std::chrono::duration<float>(now - start).count();

        if(elapsed >= 3.0f)
            break;
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Splash",0,
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoBackground);
            {
                ImGui::SetWindowPos(ImVec2(0,0));

                ImGui::SetWindowSize(ImVec2(w,h));

                ImGui::Image(
                    (ImTextureID)(intptr_t)logo,
                    ImVec2(500,250)
                );
            }

            ImGui::End();
        }

        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(
            ImGui::GetDrawData()
        );

        glfwPollEvents();

        glfwSwapBuffers(window);
    }
    if (logo != 0)
        glDeleteTextures(1, &logo);

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext(NULL);

    glfwDestroyWindow(window);
    window = nullptr;

    glfwTerminate();
}