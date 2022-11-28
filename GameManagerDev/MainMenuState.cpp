#include "MainMenuState.h"
#include "Cursor.h"
#include "Manager.h"

#include <string>

MainMenuState::MainMenuState() : cursor("../GameManagerDev/data/cursor.png")
{
	main_menu_texture.loadFromFile("../GameManagerDev/data/MainMenu/menu.png");
	main_menu_sprite.setTexture(main_menu_texture);
	button_container.push_back(
		std::make_unique<Button>(sf::IntRect(0, 0, 600, 250), 500.f, 250.f, "../GameManagerDev/data/MainMenu/buttoms.png"));
	button_container.push_back(
		std::make_unique<Button>( sf::IntRect(600,0,600,250), 500.f, 700.f, "../GameManagerDev/data/MainMenu/buttoms.png"));
}

void MainMenuState::processInput(const sf::Event& event)
{
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

void MainMenuState::update(const float& delta_time)
{
	cursor.setMouseXY(mouse_x, mouse_y);
	//start game
	if (button_container[0]->IsContains(mouse_x, mouse_y))
	{
		button_container[0]->Flicker();
		if (is_left_button_clicked)
		{
			Manager::SwitchOnState(StateTypeTask::GAME_MAIN_STATE);
		}
	}
	else
	{
		button_container[0]->StopFlicker();
	}
	//exit game
	if (button_container[1]->IsContains(mouse_x, mouse_y))
	{
		button_container[1]->Flicker();
		if (is_left_button_clicked)
		{
			Manager::SwitchOnState(StateTypeTask::CLOSE_GAME_STATE);
		}
	}
	else
	{
		button_container[1]->StopFlicker();
	}

	is_left_button_clicked = false;
}

void MainMenuState::render(sf::RenderWindow& window)
{
	
	window.draw(main_menu_sprite);
	for (size_t i = 0; i < button_container.size(); i++)
		window.draw(*button_container[i]);
	window.draw(cursor);
}
