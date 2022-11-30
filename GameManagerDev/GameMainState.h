#pragma once
#include "IState.h"
#include "GameSettings.h"
#include "Cursor.h"
#include "Chip.h"
#include "Wire.h"
#include "Cell.h"

#include <memory>
#include <vector>

class GameMainState final : public IState
{

public:
	GameMainState();

	void processInput(const sf::Event& event);
	void update(const float delta_time);
	void render(sf::RenderWindow& window) override;
private:
	void PickOrUnpickChip(const float delta_time);
	std::shared_ptr<Cell> GetCellUnderCursor(const float X, const float Y);
	std::shared_ptr<Chip> GetChipUnderCursor(const float X, const float Y);
	
	std::vector<std::shared_ptr<Cell>> AvailableCellsArray(const std::shared_ptr<Chip> sp_chip);
	bool CellIsEmpty(const std::shared_ptr<Cell> cell) const;
	//std::vector<std::shared_ptr<Cell>> GetCellArrayAroundWires(std::shared_ptr<Chip> sp_chip);

private:
	std::vector<std::shared_ptr<Chip>> chips_container;
	std::vector<std::shared_ptr<Wire>> vertical_wires_container;
	std::vector<std::shared_ptr<Wire>> horisontal_wires_container;
	std::vector<std::shared_ptr<Cell>> cells_container;
	std::vector<std::shared_ptr<Cell>> available_cells_array; //available_for_move_container


	std::shared_ptr<Chip> current_chip = nullptr;
	bool is_chip_picked = false;

	sf::Texture game_menu_texture;
	sf::Sprite game_menu_sprite;
	GameSettings game_settings;
	Cursor cursor;
	float mouse_x = 500.f;
	float mouse_y = 500.f;
	bool is_left_button_clicked = false;
};

