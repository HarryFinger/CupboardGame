#pragma once
#include "GameObject.h"

namespace
{
	const char* DEFAULT_WIN_PATH = "./data/GameState/win.png";

}

class WinObject : public GameObject
{
public:
	WinObject(const sf::IntRect& rect, const sf::Vector2f& position, const std::string& path = DEFAULT_WIN_PATH);
};