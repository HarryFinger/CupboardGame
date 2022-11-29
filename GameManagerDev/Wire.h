#pragma once
#include "GameObject.h"

const std::string DEFAULT_WIRES_PATH = "../GameManagerDev/data/GameState/wires.png";

enum class WireType
{
	Horisontal,
	Vertical
};

class Wire final : public GameObject
{
public:
	Wire(const sf::IntRect& rect, const float X, const float Y, const std::string& path = DEFAULT_WIRES_PATH);
private:
	void SetTypeOnConstruct(const sf::IntRect& rect);
	WireType path_type;
};

