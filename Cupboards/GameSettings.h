#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct VectorInt
{
    uint32_t x;
    uint32_t y;
};

class GameSettings final
{
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
    // GameData GetGameData() { return gamedata; }
    uint32_t GetLocNumber() const
    {
        return gamedata.locations_number;
    }

    uint32_t GetChipsCount() const
    {
        return gamedata.chips_count;
    }

    uint32_t GetWiresNumber() const
    {
        return gamedata.number_of_wires;
    }

    const std::vector<VectorInt> &GetLocCoordVector() const
    {
        return gamedata.locations_coordinates;
    }

    const std::vector<uint32_t> &GetStartLocations() const
    {
        return gamedata.chips_start_location;
    }

    const std::vector<uint32_t> &GetWinLocations() const
    {
        return gamedata.chips_win_location;
    }

    const std::vector<sf::Vector2f> &GetVerticalWiresVector() const
    {
        return gamedata.vertical_wires_coordinates;
    }

    const std::vector<sf::Vector2f> &GetHorisontalWiresVector() const
    {
        return gamedata.horisontal_wires_coordinates;
    }

    GameSettings(const std::string &file_path);

private:
    void ReadInVector(std::ifstream &input_data);
    bool GameDataCreator();
    void PrintGameData() const;
    bool CheckIsVectorPossibleValid() const;
    void DivideWires();
};
