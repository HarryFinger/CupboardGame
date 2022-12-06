#include "Manager.h"


Manager::Manager()
{
		current_state = std::make_unique<MainMenuState>();
		//current_state = std::make_unique<GameMainState>();
}

void Manager::processInput(const sf::Event& event)
{
	current_state->processInput(event);
}

void Manager::update(const float delta_time)
{
	SwitchStateIfNeed();
	current_state->update(delta_time);
}
void Manager::render(sf::RenderWindow& window)
{
	if (Manager::state_type_task == StateTypeTask::CLOSE_GAME_STATE)
		window.close();
	current_state->render(window);
}

void Manager::SwitchStateIfNeed()
{
	switch (Manager::state_type_task)
	{
	case StateTypeTask::DO_NOTHING:
		break;
	case StateTypeTask::MAIN_MENU_STATE:
		current_state = std::make_unique<MainMenuState>();
		Manager::state_type_task = StateTypeTask::DO_NOTHING;
		break;
	case StateTypeTask::GAME_MAIN_STATE:
		current_state = std::make_unique<GameMainState>(path_to_file);
		Manager::state_type_task = StateTypeTask::DO_NOTHING;
		break;
	case StateTypeTask::CLOSE_GAME_STATE:
		break;
	}
}

void Manager::SwitchOnState(const StateTypeTask& task, const std::string& path)
{
	path_to_file = path;
	state_type_task = task;
}

StateTypeTask Manager::state_type_task = StateTypeTask::DO_NOTHING;
std::string Manager::path_to_file = "";