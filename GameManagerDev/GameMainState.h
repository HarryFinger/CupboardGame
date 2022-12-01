#pragma once
#include "IState.h"
#include "GameSettings.h"
#include "Cursor.h"
#include "Chip.h"
#include "Wire.h"
#include "Cell.h"
#include "WinObject.h"

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
	void UnpickChip();

	std::shared_ptr<Cell> GetCellUnderCursor(const float X, const float Y);
	std::shared_ptr<Chip> GetChipUnderCursor(const float X, const float Y);
	
	std::vector<std::shared_ptr<Cell>> AvailableCellsArray(const std::shared_ptr<Chip> sp_chip);
	bool CellIsEmpty(const std::shared_ptr<Cell> cell) const;
	bool IsWireBetween(const std::shared_ptr<Chip> sp_chip, const std::shared_ptr<Cell> sp_cell) const;
	bool WireIsNear(const std::shared_ptr<Chip> sp_chip, const std::shared_ptr<Wire> sp_wire) const;
	bool IfCellIsInAvailibleArray(const std::shared_ptr<Cell> sp_cell);
	bool IsWin();

	//render
	void RenderWinPreviewMap(sf::RenderWindow& window);

private:
	std::vector<std::shared_ptr<Chip>> chips_container;
	std::vector<std::shared_ptr<Wire>> vertical_wires_container;
	std::vector<std::shared_ptr<Wire>> horisontal_wires_container;
	std::vector<std::shared_ptr<Cell>> cells_container;
	std::vector<std::shared_ptr<Cell>> available_cells_array; //container with available locations to move
	std::vector<sf::Vector2f> win_condition_container;


	std::shared_ptr<Chip> current_chip = nullptr;
	bool is_chip_picked = false;

	sf::Texture game_menu_texture;
	sf::Sprite game_menu_sprite;
	GameSettings game_settings;
	std::unique_ptr<WinObject> win_object;
	Cursor cursor;
	float mouse_x;
	float mouse_y;
	bool is_left_button_clicked = false;
	bool is_win_state = 0;
};

