#include "GameMainState.h"
#include "Manager.h"
static const float OFFSET = 50.f;
static const uint32_t MODULE = 100;

GameMainState::GameMainState(): game_settings("../GameManagerDev/data/GameState/CustomData.txt"), cursor("../GameManagerDev/data/cursor.png")
{
	game_menu_texture.loadFromFile("../GameManagerDev/data/GameState/field.png");
	game_menu_sprite.setTexture(game_menu_texture);
	
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
		size_t index = game_settings.GetStartLocVector()[i] - 1;
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
	cursor.setMouseXY(mouse_x, mouse_y);
	PickOrUnpickChip(delta_time);
	
	if (current_chip != nullptr)
	{	
		available_cells_array.clear();
		available_cells_array = AvailableCellsArray(current_chip);
		if (!available_cells_array.empty())
		{
			for (const auto& cell_el: available_cells_array)
			{
				cell_el->ChangeFrameView(FrameType::Yellow);
			}
		}
		
		auto chip = GetChipUnderCursor(mouse_x, mouse_y);
		auto cell = GetCellUnderCursor(mouse_x, mouse_y);
		// 
		// нужен массив ячеек, не занятые чипом, имеющие связи с ориджином
		// только в эти ячейки я могу муваться
		// 
		// использовать Лист?
		//1.создаем массив свободных ячеек
		//2.проверяем есть ли между ними(ячейками) и ориджином связь
		//3.если нет, выкидываем свободную ячейку из массива (или добавляем такие элементы в новый массив)
		//4.возвращаем такой массив

		//TODO availible container должен чекать связи

		if (cell && !chip )
		{
			current_chip->Move(cell.get()->getX(), cell.get()->getY());
		}
	}
	else
	{
		for (const auto& cell_el : cells_container) //change color to all cells on GREEN
		{
			cell_el->ChangeFrameView(FrameType::Green);
		}
	}

}

//RENDER STATE
void GameMainState::render(sf::RenderWindow& window)
{
	window.draw(game_menu_sprite);

	for (const auto& el : cells_container)
		window.draw(*el.get());

	for (const auto& el : chips_container)
		window.draw(*el.get());

	for (const auto& el : vertical_wires_container)
		window.draw(*el.get());

	for (const auto& el : horisontal_wires_container)
		window.draw(*el.get());


	/*for (const auto& el: available_cells_array)
		window.draw(*el.get());*/

	window.draw(cursor);
}

void GameMainState::PickOrUnpickChip(const float delta_time)
{
	if (is_left_button_clicked)
	{
		if (is_chip_picked )
		{
			//unpick state
			current_chip->StopFlicker();
			current_chip = nullptr;
			is_chip_picked = false;
		}
		else
		{
			//pick state
			for (size_t i = 0; i < chips_container.size(); i++)
			{
				if (chips_container[i]->IsContains(mouse_x, mouse_y))
				{
					current_chip = chips_container[i];
					is_chip_picked = true;
				}
			}
		}
	}
	if (current_chip != nullptr)
	{
		current_chip->Flicker(delta_time);
	}
	is_left_button_clicked = false;
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
			free_cell_array.push_back(cell_el);
		}
	}
	return free_cell_array;
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
