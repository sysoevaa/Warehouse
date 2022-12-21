#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>


class MainMenuSystem {
public:
    MainMenuSystem();
    void AddDock();
    void DrawProducts();
    void DrawShops();
    void DrawProviders();
    void DrawMain();
    void Present();

private:
    bool products_open;
    bool shops_open;
    bool prov_open;
};

