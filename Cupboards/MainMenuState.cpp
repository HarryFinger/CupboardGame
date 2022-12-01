#include "MainMenuState.h"
#include "Cursor.h"
#include "Manager.h"

#include <string>

//pathes to data
const std::string PATH_TO_LEVEL_1 = "./data/GameState/CustomData1.txt";
const std::string PATH_TO_LEVEL_2 = "./data/GameState/CustomData2.txt";
const std::string PATH_TO_LEVEL_3 = "./data/GameState/CustomData3.txt";

MainMenuState::MainMenuState() : cursor("./data/cursor.png")
{
	sf::Mouse mouse;
	mouse_x = static_cast<float>(mouse.getPosition().x);
	mouse_y = static_cast<float>(mouse.getPosition().y);

	main_menu_texture.loadFromFile("./data/MainMenu/menu.png");
	main_menu_sprite.setTexture(main_menu_texture);
	
	//1st level
	button_container.push_back(
		std::make_unique<Button>(sf::IntRect(600, 0, 600, 210), 500.f, 130.f, "./data/MainMenu/buttoms.png"));
	button_container.push_back(
		std::make_unique<Button>(sf::IntRect(1200, 0, 600, 210), 500.f, 350.f, "./data/MainMenu/buttoms.png"));
	button_container.push_back(
		std::make_unique<Button>(sf::IntRect(1800, 0, 600, 210), 500.f, 570.f, "./data/MainMenu/buttoms.png"));
	//exit button
	button_container.push_back(
		std::make_unique<Button>( sf::IntRect(0,0,600, 210), 500.f, 850.f, "./data/MainMenu/buttoms.png"));
	
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

void MainMenuState::update(const float delta_time)
{
	cursor.setMouseXY(mouse_x, mouse_y);
	
	//start game
	//1st button
	if (button_container[0]->IsContains(mouse_x, mouse_y))
	{
		button_container[0]->Flicker();
		if (is_left_button_clicked)
		{
			Manager::SwitchOnState(StateTypeTask::GAME_MAIN_STATE, PATH_TO_LEVEL_1);
		}
	}
	else button_container[0]->StopFlicker();

	//2rd button
	if (button_container[1]->IsContains(mouse_x, mouse_y))
	{
		button_container[1]->Flicker();
		if (is_left_button_clicked)
		{
			Manager::SwitchOnState(StateTypeTask::GAME_MAIN_STATE, PATH_TO_LEVEL_2);
		}
	}
	else button_container[1]->StopFlicker();

	//3rd button
	if (button_container[2]->IsContains(mouse_x, mouse_y))
	{
		button_container[2]->Flicker();
		if (is_left_button_clicked)
		{
			Manager::SwitchOnState(StateTypeTask::GAME_MAIN_STATE, PATH_TO_LEVEL_3);
		}
	}
	else button_container[2]->StopFlicker();

	//exit game
	if (button_container[3]->IsContains(mouse_x, mouse_y))
	{
		button_container[3]->Flicker();
		if (is_left_button_clicked)
		{
			Manager::SwitchOnState(StateTypeTask::CLOSE_GAME_STATE);
		}
	}
	else button_container[3]->StopFlicker();
	

	is_left_button_clicked = false;
}

void MainMenuState::render(sf::RenderWindow& window)
{
	
	window.draw(main_menu_sprite);
	for (size_t i = 0; i < button_container.size(); i++)
		window.draw(*button_container[i]);
	window.draw(cursor);
}

