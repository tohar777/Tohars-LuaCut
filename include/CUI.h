#pragma once
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <vector>
#include <string>
#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_glfw.h>
#include <ImGuiFileDialog.h>
#include <TextEditor.h>
#include <windows.h>
#include "CLuaAPI.h"
class CUI{
    private:
        int w,h;
        int current_item = 0;
        std::vector<const char*> scriptsItems;
        std::vector<std::string> paths;
        TextEditor textEditor;
        CLuaAPI lua;
    public:
        void Init(int w,int h);
        void MainMenuBar();
        void MainUI();
};