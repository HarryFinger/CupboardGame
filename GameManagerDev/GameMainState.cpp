#include "GameMainState.h"
#include "Manager.h"
static const float OFFSET = 50.f;
static const uint32_t MODULE = 100;

GameMainState::GameMainState(const std::string& path): game_settings(path), cursor("./data/cursor.png")
{
	sf::Mouse mouse;
	mouse_x = static_cast<float>(mouse.getPosition().x);
	mouse_y = static_cast<float>(mouse.getPosition().y);

	game_menu_texture.loadFromFile("./data/GameState/field.png");
	game_menu_sprite.setTexture(game_menu_texture);
	win_object = std::make_unique<WinObject>(sf::IntRect(0,0, 800, 400), 500.f, 500.f);

	//cells setup
	for (size_t i = 0; i < game_settings.GetLocNumber(); i++)
	{
		auto pair = game_settings.GetLocCoordVector()[i];
		float X = static_cast<float>(pair.x + 50);
		float Y = static_cast<float>(pair.y + 50);
		cells_container.push_back(std::make_shared<Cell>(sf::IntRect(0, 0, MODULE, MODULE), X, Y));
	}

	//chips setup
	for (size_t i = 0; i < game_settings.GetChipsCount(); i++)
	{
		size_t index = game_settings.GetStartLocations()[i] - 1;
		float X = cells_container[index]->getX();
		float Y = cells_container[index]->getY();
		chips_container.push_back(std::make_shared<Chip>(sf::IntRect(MODULE * static_cast<uint32_t>(i), 0, MODULE, MODULE), X, Y));
	}	

	//wires setup
	for (size_t i = 0; i < game_settings.GetVerticalWiresVector().size(); i++)
	{
		float X = game_settings.GetVerticalWiresVector()[i].x + OFFSET;
		float Y = game_settings.GetVerticalWiresVector()[i].y + OFFSET;
		vertical_wires_container.push_back(std::make_shared<Wire>(sf::IntRect(MODULE, 0, MODULE, MODULE), X, Y));
	}
	for (size_t i = 0; i < game_settings.GetHorisontalWiresVector().size(); i++)
	{
		float X = game_settings.GetHorisontalWiresVector()[i].x + OFFSET;
		float Y = game_settings.GetHorisontalWiresVector()[i].y + OFFSET;
		horisontal_wires_container.push_back(std::make_shared<Wire>(sf::IntRect(0, 0, MODULE, MODULE), X, Y));
	}

	//win condition setup
	for (size_t i = 0; i < game_settings.GetChipsCount(); i++)
	{
		size_t index = game_settings.GetWinLocations()[i] - 1;
		float X = cells_container[index]->getX();
		float Y = cells_container[index]->getY();
		win_condition_container.push_back(sf::Vector2f(X, Y));
	}
}

//INPUT STATE
void GameMainState::processInput(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Escape && (event.type == sf::Event::KeyPressed))
		Manager::SwitchOnState(StateTypeTask::MAIN_MENU_STATE);
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			is_left_button_clicked = true;
		}
	}

	if (event.type == sf::Event::MouseMoved)
	{
		mouse_x = static_cast<float>(event.mouseMove.x);
		mouse_y = static_cast<float>(event.mouseMove.y);
	}
}

//UPDATE STATE
void GameMainState::update(const float delta_time)
{
	cursor.setMouseXY(mouse_x, mouse_y); //cursor movement
	cursor.update(delta_time);

	switch (game_phase)
	{
	case GamePhase::Common:
	{
		if (IsWin())
		{
			game_phase = GamePhase::Win;
			break;
		}

		for (const auto& cell_el : cells_container)
		{
			cell_el->ChangeFrameView(FrameType::Green);
		}

		PickChip();
		
		if (is_chip_picked)
		{
			game_phase = GamePhase::Picked;
		}
	}
		break;
	case GamePhase::Picked:
	{
		if (current_chip != nullptr)
		{
			current_chip->Flicker(delta_time);
			available_cells_array.clear();
			available_cells_array = AvailableCellsArray(current_chip);
			if (!available_cells_array.empty())
			{
				for (const auto& cell_el : available_cells_array)
				{
					cell_el->ChangeFrameView(FrameType::Yellow);
				}
				target_cell = GetCellUnderCursor(mouse_x, mouse_y);
				if (target_cell != nullptr)
				{
					if (IfCellIsInAvailibleArray(target_cell))
					{
						if (is_left_button_clicked)
						{
							delta_for_anim_X = current_chip->getX() - target_cell->getX();
							delta_for_anim_Y = current_chip->getY() - target_cell->getY();

							game_phase = GamePhase::Animation;
							break;
						}
					}
				}
			}
			if (is_left_button_clicked)
			{
				UnpickChip();
				game_phase = GamePhase::Common;
			}
		}
	}
		break;
	case GamePhase::Animation:
	{
		current_chip->StopFlicker();

		for (const auto& cell_el : cells_container)
		{
			cell_el->ChangeFrameView(FrameType::Green);
		}

		if (anim_timer < time_to_animation)
		{
			float stepX = (delta_time * delta_for_anim_X) / time_to_animation;
			float stepY = (delta_time * delta_for_anim_Y) / time_to_animation;
			float curX = current_chip->getX();
			float curY = current_chip->getY();
			current_chip->setObjectXY(curX - stepX, curY - stepY);
			anim_timer += delta_time;
		}
		else
		{
			current_chip->setObjectXY(target_cell->getX(), target_cell->getY());
			UnpickChip();
			anim_timer = 0.f;
			game_phase = GamePhase::Common;
		}
	}
		break;
	case GamePhase::Win:
	{
		is_win_state = true;
	}
		break;
	}

	is_left_button_clicked = false;
}

//RENDER STATE
void GameMainState::render(sf::RenderWindow& window)
{
	window.draw(game_menu_sprite);

	for (const auto& el : vertical_wires_container)
		window.draw(*el.get());

	for (const auto& el : horisontal_wires_container)
		window.draw(*el.get());

	for (const auto& el : cells_container)
		window.draw(*el.get());

	for (const auto& el : chips_container)
		window.draw(*el.get());

	RenderWinPreviewMap(window);

	if (is_win_state)
		window.draw(*win_object.get());

	window.draw(cursor);
}

void GameMainState::PickChip()
{
	if (is_left_button_clicked)
	{
		for (const auto& chip_el : chips_container)
		{
			if (chip_el->IsContains(mouse_x, mouse_y))
			{
				current_chip = chip_el;
				is_chip_picked = true;
				is_left_button_clicked = false;
			}
		}
	}
}

void GameMainState::UnpickChip()
{
	if (is_chip_picked && current_chip != nullptr)
	{
		current_chip->StopFlicker();
		current_chip = nullptr;
		is_chip_picked = false;
		is_left_button_clicked = false;
	}
}

std::shared_ptr<Cell> GameMainState::GetCellUnderCursor(const float X, const float Y)
{
	for (const auto& el : cells_container)
	{
		if (el.get()->IsContains(X, Y)) 
		{
			return el;
		}
	}
	return nullptr;
}

std::shared_ptr<Chip> GameMainState::GetChipUnderCursor(const float X, const float Y)
{
	for (const auto& el : chips_container)
	{
		if (el.get()->IsContains(X, Y))
		{
			return el;
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<Cell>> GameMainState::AvailableCellsArray(const std::shared_ptr<Chip> sp_chip)
{
	std::vector<std::shared_ptr<Cell>> free_cell_array;
	for (const auto& cell_el : cells_container)
	{
		if (CellIsEmpty(cell_el))
		{
			if (IsWireBetween(sp_chip, cell_el))
			{
				free_cell_array.push_back(cell_el);
			}
		}
	}
	return free_cell_array;
}

bool GameMainState::IfCellIsInAvailibleArray(const std::shared_ptr<Cell> sp_cell)
{
	float cellX = sp_cell->getX();
	float cellY = sp_cell->getY();
	for (const auto& cell_el : available_cells_array)
	{
		if (cell_el->IsContains(cellX, cellY))
		{
			return true;
		}
	}
	return false;
}

bool GameMainState::CellIsEmpty(const std::shared_ptr<Cell> cell) const
{
	bool is_empty = 0;
	for (const auto& chip_el : chips_container)
	{
		if (cell->IsContains(chip_el->getX(), chip_el->getY()))
		{
			is_empty = 0;
			return is_empty;
		}
		else
		{
			is_empty = 1;
		}
	}
	return is_empty;
}

bool GameMainState::IsWireBetween(const std::shared_ptr<Chip> sp_chip, const std::shared_ptr<Cell> sp_cell) const
{
	float chipX = sp_chip->getX();
	float chipY = sp_chip->getY();
	float cellX = sp_cell->getX();
	float cellY = sp_cell->getY();

	float resultX = (chipX + cellX) / 2;
	float resultY = (chipY + cellY) / 2;

	for (const auto& wire_el : vertical_wires_container)
	{
		if (wire_el->IsContains(resultX, resultY) && WireIsNear(sp_chip, wire_el))
		{
			return true;
		}
	}
	for (const auto& wire_el : horisontal_wires_container)
	{
		if (wire_el->IsContains(resultX, resultY) && WireIsNear(sp_chip, wire_el))
		{
			return true;
		}
	}
	return false;
}

//TO DO!!!!!!!!!!!!!!!!!!!!!!!!
bool GameMainState::WireIsNear(const std::shared_ptr<Chip> sp_chip, const std::shared_ptr<Wire> sp_wire) const
{
	float chipX = sp_chip->getX();
	float chipY = sp_chip->getY();

	float option1X = chipX - MODULE;
	float option1Y = chipY;
	float option2X = chipX + MODULE;
	float option2Y = chipY;

	float option3X = chipX;
	float option3Y = chipY - MODULE;
	float option4X = chipX;
	float option4Y = chipY + MODULE;

	if (sp_wire->IsContains(option1X, option1Y))
		return true;
	if (sp_wire->IsContains(option2X, option2Y))
		return true;
	if (sp_wire->IsContains(option3X, option3Y))
		return true;
	if (sp_wire->IsContains(option4X, option4Y))
		return true;

	return false;
}


bool GameMainState::IsWin()
{
	for (size_t i = 0; i < chips_container.size(); i++)
	{
		if ((chips_container[i]->getX() == win_condition_container[i].x) && 
			((chips_container[i]->getY() == win_condition_container[i].y)))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

void GameMainState::RenderWinPreviewMap(sf::RenderWindow& window)
{
	for (size_t i = 0; i < chips_container.size(); i++)
	{
		const float offsetX = 498;
		const float offsetY = 670;
		const float compression_ratio = 0.45f;
		const sf::Vector2f scale(0.45f, 0.45f);
		
		sf::Sprite prev_sprite = chips_container[i]->GetSprite();
		prev_sprite.setPosition(sf::Vector2f(
			win_condition_container[i].x * compression_ratio + offsetX , win_condition_container[i].y * compression_ratio + offsetY));
		prev_sprite.setScale(scale);
		window.draw(prev_sprite);
	}
}