#include "MainMenuSystem.h"
#include "Warehouse.h"
#include "Config.h"

MainMenuSystem::MainMenuSystem() {
    this->settings_open = true;
}


void MainMenuSystem::AddDock() {
    if (!ImGui::BeginMainMenuBar()) {
        return;
    }
    if (ImGui::MenuItem("Settings", 0, &this->settings_open)) {

    }
    ImGui::EndMainMenuBar();
}
void MainMenuSystem::DrawSettings() {
    ImGui::SetNextWindowSize(ImVec2(500, 600));
    ImGui::Begin("Settings", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    Warehouse::g_Instance->GetConfig()->Present();

    ImGui::End();
}

void MainMenuSystem::Present() {
    //ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_FirstUseEver);
    this->AddDock();
    this->DrawMain();
    if (this->settings_open) this->DrawSettings();
}

void MainMenuSystem::DrawMain() {
    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::Begin("Main", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);

    Warehouse::g_Instance->Present();

    ImGui::End();
}