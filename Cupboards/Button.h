#pragma once
#include "GameObject.h"

class Button final : public GameObject
{
public:
	Button( const sf::IntRect& rect, const sf::Vector2f& position, const std::string& path);
	void Flicker();
	void StopFlicker();
private:
	sf::Vector2f original_scale;
	sf::Color original_color;
};

