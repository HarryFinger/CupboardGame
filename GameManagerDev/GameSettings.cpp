#include "GameSettings.h"
#include <cctype>
#include <sstream>

GameSettings::GameSettings(const std::string& file_path)
{
	std::ifstream input_data;
	input_data.open(file_path);

	if (!input_data.is_open())
	{
		std::cerr << "File \"" << file_path << "\" is not opened\n";
		return;
	}

	ReadInVector(input_data);
	if (!CheckIsVectorPossibleValid())
	{
		std::cerr << "Vector is NOT valid\n";
		return;
	}
	else
	{
#ifdef GAME_DEBUG
		std::cout << "Vector is possible valid\n";
#endif //GAME_DEBUG
	}

	GameDataCreator();
#ifdef GAME_DEBUG
	PrintGameData();
#endif //GAME_DEBUG
	DivideWires();
	input_data.close();
}

void GameSettings::ReadInVector(std::ifstream& input_data)
{
	while (!input_data.eof())
	{
		if (!std::isdigit(input_data.peek()))
		{
			input_data.get();
		}
		else
		{
			uint32_t value;
			input_data >> value;
			data_vector.push_back(value);
		}
	}
}

void GameSettings::GameDataCreator()
{
	size_t index = 0;
	gamedata.locations_number = data_vector[index++];
	gamedata.chips_count = data_vector[index++];
	gamedata.number_of_wires = data_vector[index++];

	size_t locations_coordinates_size = gamedata.locations_number * 2 + index;
	while (index < locations_coordinates_size)
	{
		gamedata.locations_coordinates.push_back(VectorInt(data_vector[index], data_vector[index + 1]));
		index += 2;
	}

	size_t chips_start_location_size = gamedata.chips_count + index;
	while (index < chips_start_location_size)
	{
		gamedata.chips_start_location.push_back(data_vector[index]);
		index++;
	}

	size_t chips_win_location_size = gamedata.chips_count + index;
	while (index < chips_win_location_size)
	{
		gamedata.chips_win_location.push_back(data_vector[index]);
		index++;
	}

	size_t wires_size = gamedata.number_of_wires * 2 + index;
	while (index < wires_size)
	{
		gamedata.wires.push_back(VectorInt(data_vector[index], data_vector[index + 1]));
		index += 2;
	}
#ifdef GAME_DEBUG
	if (data_vector.size() == index)
	{
		std::cout << "GameData build success" << std::endl;
		data_vector.clear();
	}
#endif //GAME_DEBUG
}

void GameSettings::PrintGameData()
{
	std::cout << gamedata.locations_number << "\n";
	std::cout << gamedata.chips_count << "\n";
	std::cout << gamedata.number_of_wires << "\n";
	for (const auto& it : gamedata.locations_coordinates)
		std::cout << it.x << "," << it.y << " ";
	std::cout << "\n";
	for (const auto& it : gamedata.chips_start_location)
		std::cout << it << " ";
	std::cout << "\n";
	for (const auto& it : gamedata.chips_win_location)
		std::cout << it << " ";
	std::cout << "\n";
	for (const auto& it : gamedata.wires)
		std::cout << it.x << "," << it.y << " ";
}

//simple basic check
bool GameSettings::CheckIsVectorPossibleValid()
{
	uint32_t control_sum = data_vector[0] * 2 + data_vector[1] * 2 + data_vector[2] * 2 + 3;
	return (control_sum == data_vector.size());
}

void GameSettings::DivideWires()
{
	for (size_t i = 0; i < gamedata.number_of_wires; i++)
	{
		
		size_t first_location_index = gamedata.wires[i].x - 1;
		size_t second_location_index = gamedata.wires[i].y - 1;
		uint32_t first_x = gamedata.locations_coordinates[first_location_index].x;
		uint32_t second_x = gamedata.locations_coordinates[second_location_index].x;
		uint32_t first_y = gamedata.locations_coordinates[first_location_index].y;
		uint32_t second_y = gamedata.locations_coordinates[second_location_index].y;
		if (first_x == second_x)
		{
			gamedata.vertical_wires_coordinates.push_back(sf::Vector2f(static_cast<float>(first_x), static_cast<float>((first_y + second_y)/2)));
		}
		if (first_y == second_y)
		{
			gamedata.horisontal_wires_coordinates.push_back(sf::Vector2f(static_cast<float>((first_x + second_x)/2), static_cast<float>(first_y)));
		}
	}
}

