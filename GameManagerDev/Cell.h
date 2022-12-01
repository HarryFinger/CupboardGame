#pragma once
#include "GameObject.h"

static const std::string DEFAULT_CELLS_PATH = "../GameManagerDev/data/GameState/cells.png";

enum class FrameType
{
	Green,
	Yellow
};

class Cell final : public GameObject
{
public:
	Cell(const sf::IntRect& rect, const float X, const float Y, const std::string& path = DEFAULT_CELLS_PATH);
	void ChangeFrameView(const FrameType& frame_type);
private:
	FrameType frame_type = FrameType::Green;
};

