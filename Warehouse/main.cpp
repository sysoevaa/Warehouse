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

#include "MainMenuSystem.h"
#include "Warehouse.h"
#include "Config.h"

using std::cin;
using std::cout;
using std::endl;

class Bootstrapper {
public:
    Bootstrapper() {
        this->menu = new MainMenuSystem();
        this->wnd.create(sf::VideoMode(900, 900), "");
        this->wnd.setFramerateLimit(144);
        this->deltaClock.restart();
        ImGui::SFML::Init(this->wnd);

        this->simCfg = Config::CreateDefault();
        this->warehouse = new Warehouse(this->simCfg);
    }
    ~Bootstrapper() {
        ImGui::SFML::Shutdown();
        if(this->menu) delete this->menu;
        this->menu = nullptr;
    }

    void Present() {
        sf::Event event;
        while (this->wnd.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                this->wnd.close();
                return;
            }
        }

        ImGui::SFML::Update(this->wnd, deltaClock.restart());

        //ImGui::ShowDemoWindow();

        this->menu->Present();

        this->wnd.clear();
        ImGui::SFML::Render(this->wnd);
        this->wnd.display();
    }

    void Update() {
        this->warehouse->Update();
    }

    void UpdateOne() {
        this->Update();
        this->Present();
    }

    bool IsAlive() {
        return this->wnd.isOpen();
    }

    void Start() {
        while (this->IsAlive()) {
            this->UpdateOne();
        }
    }

private:
    Config* simCfg;
    MainMenuSystem* menu;
    Warehouse* warehouse;

    sf::RenderWindow wnd;
    sf::Clock deltaClock;
};

int main(int argc, void* argv) {
    Bootstrapper component;
    component.Start();
    return 0;
}