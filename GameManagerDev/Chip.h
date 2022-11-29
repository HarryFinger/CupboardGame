#pragma once
#include "GameObject.h"

const std::string DEFAULT_CHIP_PATH = "../GameManagerDev/data/GameState/chips.png";

enum class ChipType
{
	Green,
	Magenta,
	Blue,
	Yellow,
	Red,
	Black,
	White,
	Orange,
	Cyan
};

class Chip final : public GameObject
{
public:
	Chip(const sf::IntRect& rect, const float X, const float Y, const std::string& path = DEFAULT_CHIP_PATH);
	void Flicker(const float delta_time);
	void StopFlicker();
	void Move(const float X, const float Y);
private:
	void SetTypeOnConstruct(const sf::IntRect& rect);
	sf::Vector2f original_scale;
	sf::Color original_color;
	ChipType chip_type;

	float time_accumulator = 0;
	float frequency = 8;
};

