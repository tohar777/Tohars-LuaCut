#include "CUI.h"

void CUI::Init(int w, int h)
{
    this->w = w;
    this->h = h;
    lua.InitAPI();
}

void CUI::MainMenuBar(){
    if(ImGui::BeginMainMenuBar()){

        ImGui::Text("Tohars LuaCut 0.2");
        if(ImGui::BeginMenu("File")){
            if(ImGui::MenuItem("Import")){
                ImGuiFileDialog::Instance()->OpenDialog("Choose a Script to add", "Choose File", ".lua, .bundle");
            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Scripts")){
            if(ImGui::MenuItem("Create script")){
                MessageBoxA(nullptr,"A .lua template was created. \n please use an text editor of your choose","",MB_OK | MB_ICONINFORMATION);
            }
            if(ImGui::MenuItem("Create a .bundle")){
                MessageBoxA(nullptr,"A .bundle template was created. \n please use an text editor of your choose with XML support","",MB_OK | MB_ICONINFORMATION);
            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help")){
            if(ImGui::MenuItem("About LuaCut")){
                MessageBoxA(nullptr,"Tohars LuaCut 0.2(C) 2026(C) \n copyright under the GPL 3.0","About Tohars LuaCut 1.0",MB_OK | MB_ICONINFORMATION);
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    {
        ImGui::SetNextWindowSize(ImVec2(50,200), ImGuiCond_FirstUseEver);
        if(ImGuiFileDialog::Instance()->Display("Choose a Script to add")){
            if(ImGuiFileDialog::Instance()->IsOk()){
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                paths.push_back(filePath);
                printf("Selected: %s\n", filePath.c_str());
            }

            ImGuiFileDialog::Instance()->Close();
        }
    }
}

void CUI::MainUI(){
   ImGui::Begin("Main",0,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
   {
    ImGui::SetWindowPos(ImVec2(0,19));
    ImGui::SetWindowSize(ImVec2(w,h-19));
    if(ImGui::Button("Create New")){

    }
    if(ImGui::Button("Import")){
        ImGuiFileDialog::Instance()->OpenDialog("Choose a Script to add", "Choose File", ".lua, .bundle");
    }
    ImGui::SeparatorText("Run Scripts");
    scriptsItems.clear();
    for(const auto& path : paths){
        scriptsItems.push_back(path.c_str());
    }
    ImGui::Combo("Scripts", &current_item, scriptsItems.data(), scriptsItems.size());
    if(ImGui::Button("Run Selected Script")){
        lua.RunScript(paths[current_item].c_str());
    }
   }
   ImGui::End();
}