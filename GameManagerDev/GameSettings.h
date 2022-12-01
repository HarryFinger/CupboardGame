#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>

struct VectorInt
{
	uint32_t x;
	uint32_t y;
};

class GameSettings final
{
public:
	
private:
	std::vector<uint32_t> data_vector;
	struct GameData
	{
		uint32_t locations_number;
		uint32_t chips_count;
		uint32_t number_of_wires;
		std::vector<VectorInt> locations_coordinates;
		std::vector<uint32_t> chips_start_location;
		std::vector<uint32_t> chips_win_location;
		std::vector<VectorInt> wires;
		std::vector<sf::Vector2f> vertical_wires_coordinates;
		std::vector<sf::Vector2f> horisontal_wires_coordinates;
	} gamedata;

public:
	//GameData GetGameData() { return gamedata; }
	uint32_t GetLocNumber() { return gamedata.locations_number; }
	uint32_t GetChipsCount() { return gamedata.chips_count; }
	uint32_t GetWiresNumber() { return gamedata.number_of_wires; }
	std::vector<VectorInt> GetLocCoordVector() { return gamedata.locations_coordinates; }
	std::vector<uint32_t> GetStartLocations() { return gamedata.chips_start_location; }
	std::vector<uint32_t> GetWinLocations() { return gamedata.chips_win_location; }
	std::vector<sf::Vector2f> GetVerticalWiresVector() { return gamedata.vertical_wires_coordinates; }
	std::vector<sf::Vector2f> GetHorisontalWiresVector() { return gamedata.horisontal_wires_coordinates; }


	GameSettings(const std::string& file_path);
private:
	void ReadInVector(std::ifstream& input_data);
	void GameDataCreator();
	void PrintGameData();
	bool CheckIsVectorPossibleValid();
	void DivideWires();
};

