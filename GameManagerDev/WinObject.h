#pragma once
#include "GameObject.h"

static const std::string DEFAULT_WIN_PATH = "../GameManagerDev/data/GameState/win.png";

class WinObject : public GameObject
{
public:
	WinObject(const sf::IntRect& rect, const float X, const float Y, const std::string& path = DEFAULT_WIN_PATH);
};