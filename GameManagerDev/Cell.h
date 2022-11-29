#pragma once
#include "GameObject.h"

const std::string DEFAULT_CELLS_PATH = "../GameManagerDev/data/GameState/cells.png";

class Cell final : public GameObject
{
public:
	Cell(const sf::IntRect& rect, const float X, const float Y, const std::string& path = DEFAULT_CELLS_PATH);
private:
};

