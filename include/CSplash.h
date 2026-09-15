#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_glfw.h>
#include "CUI.h"

class CSplash{
    public:
        GLFWwindow* window = nullptr;
    public:
        int LCCreateWindow();
        void LCInitUI();
        void LCRun();
};