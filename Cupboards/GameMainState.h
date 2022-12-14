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
	GameMainState(const std::string& path);

	void processInput(const sf::Event& event);
	void update(const float delta_time);
	void render(sf::RenderWindow& window) override;

private:
	void PickChip();
	void UnpickChip();

	Cell* GetCellUnderCursor (const sf::Vector2f& vec) const;
	Chip* GetChipUnderCursor (const sf::Vector2f& vec) const;
	
	std::vector<Cell*> AvailableCellsArray(Chip* sp_chip);
	bool CellIsEmpty(Cell* cell) const;
	bool IsWireBetween(Chip* sp_chip, Cell* sp_cell) const;
	bool WireIsNear(Chip* sp_chip, Wire* sp_wire) const;
	bool IfCellIsInAvailibleArray(Cell* sp_cell) const;
	bool IsWin() const;

	//render
	void RenderWinPreviewMap(sf::RenderWindow& window);

private:
	enum class GamePhase
	{
		Common,
		Picked,
		Animation,
		Win
	} game_phase = GamePhase::Common;

	std::vector<std::unique_ptr<Chip>> chips_container;
	std::vector<std::unique_ptr<Wire>> vertical_wires_container;
	std::vector<std::unique_ptr<Wire>> horisontal_wires_container;
	std::vector<std::unique_ptr<Cell>> cells_container;
	
	std::vector<Cell*> available_cells_array; //container with available locations to move
	std::vector<sf::Vector2f> win_condition_container;

	Cell* target_cell = nullptr;
	Chip* current_chip = nullptr;

	sf::Texture game_menu_texture;
	sf::Sprite game_menu_sprite;
	GameSettings game_settings;
	std::unique_ptr<WinObject> win_object;
	Cursor cursor;

	float delta_for_anim_X;
	float delta_for_anim_Y;
	float anim_timer = 0.f;
	float time_to_animation = 0.35f;

	bool is_left_button_clicked = false;
	bool is_chip_picked = false;
	bool is_win_state = 0;
};

