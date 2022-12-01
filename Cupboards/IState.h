#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class IState
{
public:
	IState() {};

	virtual void processInput(const sf::Event& event) = 0;
	virtual void update(const float delta_time) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};