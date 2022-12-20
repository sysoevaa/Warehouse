#include "MainMenuSystem.h"

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
    ImGui::SetNextWindowSize(ImVec2(300, 200));
    ImGui::Begin("Settings", 0, ImGuiWindowFlags_NoResize);



    ImGui::End();
}

void MainMenuSystem::Present() {
    //ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_FirstUseEver);
    this->AddDock();
    if (this->settings_open) this->DrawSettings();

}