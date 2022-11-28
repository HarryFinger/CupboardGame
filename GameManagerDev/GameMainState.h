#pragma once
#include "IState.h"
#include "GameSettings.h"
#include "Cursor.h"
#include "Chip.h"
#include "Wire.h"
#include "Cell.h"

#include <memory>
#include <vector>

class GameMainState : public IState
{

public:
	GameMainState();

	void processInput(const sf::Event& event);
	void update(const float& delta_time);
	void render(sf::RenderWindow& window) override;

private:
	std::vector<std::unique_ptr<Chip>> chips_container;
	std::vector<std::unique_ptr<Wire>> vertical_wires_container;
	std::vector<std::unique_ptr<Wire>> horisontal_wires_container;
	std::vector<std::unique_ptr<Cell>> cells_container;

	sf::Texture game_menu_texture;
	sf::Sprite game_menu_sprite;
	GameSettings game_settings;
	Cursor cursor;
	float mouse_x = 500.f;
	float mouse_y = 500.f;
	bool is_left_button_clicked = false;
};

