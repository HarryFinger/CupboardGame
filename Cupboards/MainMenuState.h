#pragma once
#include "Button.h"
#include "Cursor.h"
#include "IState.h"

#include <memory>
#include <vector>

class MainMenuState final : public IState
{

public:
    MainMenuState();
    void processInput(const sf::Event &event) override;
    void update(const float delta_time);
    void render(sf::RenderWindow &window) override;

private:
    std::vector<std::unique_ptr<Button>> button_container;

    sf::Texture main_menu_texture;
    sf::Sprite main_menu_sprite;
    Cursor cursor;
    bool is_left_button_clicked = false;
};
