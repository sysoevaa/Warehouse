#include "MainMenuSystem.h"
#include "Warehouse.h"
#include "Config.h"

MainMenuSystem::MainMenuSystem() {
    this->products_open = true;
    this->shops_open = false;
    this->prov_open = false;
}


void MainMenuSystem::AddDock() {
    if (!ImGui::BeginMainMenuBar()) {
        return;
    }
    if (ImGui::MenuItem("Products", 0, &this->products_open)) {}
    if (ImGui::MenuItem("Shops", 0, &this->shops_open)) {}
    //if (ImGui::MenuItem("Providers", 0, &this->prov_open)) {}
    ImGui::EndMainMenuBar();
}
void MainMenuSystem::DrawProducts() {
    ImGui::SetNextWindowSize(ImVec2(700, 600));
    ImGui::Begin("Products", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    Warehouse::g_Instance->GetConfig()->DrawProducts();

    ImGui::End();
}
void MainMenuSystem::DrawShops() {
    ImGui::SetNextWindowSize(ImVec2(700, 600));
    ImGui::Begin("Shops", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    Warehouse::g_Instance->GetConfig()->DrawShops();

    ImGui::End();
}

void MainMenuSystem::DrawProviders() {
    ImGui::SetNextWindowSize(ImVec2(700, 600));
    ImGui::Begin("Providers", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    Warehouse::g_Instance->GetConfig()->DrawProviders();

    ImGui::End();
}

void MainMenuSystem::Present() {
    //ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_FirstUseEver);
    this->AddDock();
    this->DrawMain();
    if (this->products_open) this->DrawProducts();
    if (this->shops_open) this->DrawShops();
    if (this->prov_open) this->DrawProviders();

}

void MainMenuSystem::DrawMain() {
    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::SetNextWindowSize(ImVec2(1000, 700));
    if (ImGui::Begin("Main", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration)) {
        Warehouse::g_Instance->Present();

        ImGui::End();
    }
}