#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_glfw.h>
#include "CUI.h"

class CApplication{
    public:
        GLFWwindow* window = nullptr;
        CUI ui;
    public:
        int LCCreateWindow();
        void LCInitUI();
        void LCRun();
};