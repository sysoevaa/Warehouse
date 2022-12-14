#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

using std::cin;
using std::cout;
using std::endl;

class MainMenuSystem {
public:
    
    void AddDock() {
        if (!ImGui::BeginMainMenuBar()) {
            return;
        }
        if (ImGui::MenuItem("Settings")) {

        }
        ImGui::EndMainMenuBar();
    }

    void Present() {
        this->AddDock();

    }

private:
    bool settings_;
};


int main(int argc, void* argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "");
    window.setFramerateLimit(144);
    ImGui::SFML::Init(window);

    MainMenuSystem mainMenu;


    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_FirstUseEver);
        ImGui::ShowDemoWindow();

        mainMenu.Present();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}