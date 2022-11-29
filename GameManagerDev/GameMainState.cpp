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

void GameMainState::update(const float delta_time)
{
	cursor.setMouseXY(mouse_x, mouse_y);
	PickOrUnpickChip(delta_time);
	
	if (current_chip != nullptr)
	{	
		auto chip = GetChipUnderCursor(mouse_x, mouse_y);
		auto cell = GetCellUnderCursor(mouse_x, mouse_y);
		// нужен массив ячеек, не занятые чипом, имеющие связи с ориджином
		// только в эти ячейки я могу муваться
		// 
		// использовать Лист?
		//1.создаем массив свободных ячеек
		//2.проверяем есть ли между ними(ячейками) и ориджином связь
		//3.если нет, выкидываем свободную ячейку из массива (или добавляем такие элементы в новый массив)
		//4.возвращаем такой массив

		if (cell && !chip )
		{
			current_chip->Move(cell.get()->getX(), cell.get()->getY());
		}
	}

}

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

bool GameMainState::IsAnyWiresAround(std::shared_ptr<Chip> sp_chip)
{
	float X = sp_chip->getX();
	float Y = sp_chip->getY();
	for (const auto& el : vertical_wires_container)
	{
		if (el->IsContains(X, Y - MODULE))
		{
			std::cout << "CONTAINS WIRE\n";
			return true;
		}
		if (el->IsContains(X, Y + MODULE))
		{
			std::cout << "CONTAINS WIRE\n";
			return true;
		}
	}
	for (const auto& el : horisontal_wires_container)
	{
		if (el->IsContains(X - MODULE, Y))
		{
			std::cout << "CONTAINS WIRE\n";
			return true;
		}
		if (el->IsContains(X + MODULE, Y))
		{
			std::cout << "CONTAINS WIRE\n";
			return true;
		}
	}

	return false;
}

//std::vector<std::shared_ptr<Cell>> GameMainState::GetCellArrayAroundWires(std::shared_ptr<Chip> sp_chip)
//{
//	std::vector<std::shared_ptr<Wire>> wires_arround_array;
//	float X = sp_chip->getX();
//	float Y = sp_chip->getY();
//	for (const auto& el : vertical_wires_container)
//	{
//		if (el->IsContains(X, Y - MODULE))
//		{
//			wires_arround_array.push_back(el);
//		}
//		if (el->IsContains(X, Y + MODULE))
//		{
//			wires_arround_array.push_back(el);
//		}
//	}
//	for (const auto& el : horisontal_wires_container)
//	{
//		if (el->IsContains(X - MODULE, Y))
//		{
//			wires_arround_array.push_back(el);
//		}
//		if (el->IsContains(X + MODULE, Y))
//		{
//			wires_arround_array.push_back(el);
//		}
//	}
//	std::vector<std::shared_ptr<Cell>> cell_array_around_wires;
//
//	for (const auto& el : wires_arround_array)
//	{
//		float X = el->getX();
//		float Y = el->getY();
//		for (const auto& cell_el : cells_container)
//		{
//			if (cell_el->IsContains(X, Y - MODULE))
//			{
//				cell_array_around_wires.push_back(cell_el);
//			}
//			if (cell_el->IsContains(X, Y + MODULE))
//			{
//				cell_array_around_wires.push_back(cell_el);
//			}
//			if (cell_el->IsContains(X - MODULE, Y))
//			{
//				cell_array_around_wires.push_back(cell_el);
//			}
//			if (cell_el->IsContains(X + MODULE, Y))
//			{
//				cell_array_around_wires.push_back(cell_el);
//			}
//		}
//	}
//
//	return cell_array_around_wires;
//}