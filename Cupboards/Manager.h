#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Cursor.h"
#include "GameMainState.h"
#include "IState.h"
#include "MainMenuState.h"

enum class StateTypeTask
{
    DO_NOTHING,
    MAIN_MENU_STATE,
    GAME_MAIN_STATE,
    CLOSE_GAME_STATE
};

class Manager final
{
private:
    static StateTypeTask state_type_task;
    std::unique_ptr<IState> current_state;
    sf::RenderWindow *window;
    static std::string path_to_file;

public:
    Manager();

    void processInput(const sf::Event &event);
    void update(const float delta_time);
    void render(sf::RenderWindow &window);
    static void SwitchOnState(const StateTypeTask &task, const std::string &path_to_file = "");

private:
    void SwitchStateIfNeed();
};
