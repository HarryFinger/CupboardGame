#include "GameMainState.h"
#include "Manager.h"
//const float OFFSET = 50.f;

GameMainState::GameMainState(): game_settings("../GameManagerDev/data/GameState/CustomData.txt"), cursor("../GameManagerDev/data/cursor.png")
{
	game_menu_texture.loadFromFile("../GameManagerDev/data/GameState/field.png");
	game_menu_sprite.setTexture(game_menu_texture);
	
	//cells
	for (size_t i = 0; i < game_settings.GetLocNumber(); i++)
	{
		auto pair = game_settings.GetLocCoordVector()[i];
		float X = static_cast<float>(pair.x + 50);
		float Y = static_cast<float>(pair.y + 50);
		cells_container.push_back(std::make_unique<Cell>(sf::IntRect(0, 0, 100, 100), X, Y));
	}

	//chips
	for (size_t i = 0; i < game_settings.GetChipsCount(); i++)
	{
		size_t index = game_settings.GetStartLocVector()[i] - 1;
		float X = cells_container[index]->getX();
		float Y = cells_container[index]->getY();
		chips_container.push_back(std::make_unique<Chip>(sf::IntRect(0, 0, 100, 100), X, Y));
	}

	//wires
	for (size_t i = 0; i < game_settings.GetVerticalWiresVector().size(); i++)
	{
		float X = game_settings.GetVerticalWiresVector()[i].x + 50.f;
		float Y = game_settings.GetVerticalWiresVector()[i].y + 50.f;
		vertical_wires_container.push_back(std::make_unique<Wire>(sf::IntRect(100, 0, 100, 100), X, Y));
	}
	for (size_t i = 0; i < game_settings.GetHorisontalWiresVector().size(); i++)
	{
		float X = game_settings.GetHorisontalWiresVector()[i].x + 50.f;
		float Y = game_settings.GetHorisontalWiresVector()[i].y + 50.f;
		horisontal_wires_container.push_back(std::make_unique<Wire>(sf::IntRect(0, 0, 100, 100), X, Y));
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

void GameMainState::update(const float& delta_time)
{
	cursor.setMouseXY(mouse_x, mouse_y);
	for (size_t i = 0; i < chips_container.size(); i++)
	{
		if (chips_container[i]->IsContains(mouse_x, mouse_y))
		{
			std::cout << i << " contains mouse\n";
		}
	}
}

void GameMainState::render(sf::RenderWindow& window)
{
	window.draw(game_menu_sprite);
	
	for (size_t i = 0; i < cells_container.size(); i++)
	{
		window.draw(*cells_container[i]);
	}
	for (size_t i = 0; i < chips_container.size(); i++)
	{
		window.draw(*chips_container[i]);
	}
	for (size_t i = 0; i < vertical_wires_container.size(); i++)
	{
		window.draw(*vertical_wires_container[i]);
	}
	for (size_t i = 0; i < horisontal_wires_container.size(); i++)
	{
		window.draw(*horisontal_wires_container[i]);
	}
	window.draw(cursor);
}