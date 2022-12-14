#include "Chip.h"

#include <iostream>

Chip::Chip(const sf::IntRect& rect, const sf::Vector2f& position, const std::string& path) :
	GameObject(rect, position, path)
{
	SetTypeOnConstruct(rect);
	original_color = sprite.getColor();
}

void Chip::Flicker(const float delta_time)
{
	time_accumulator += delta_time; //potential inf
	sf::Uint8 opasity = (sin(time_accumulator * frequency) + 1)*90 + 65;

	sprite.setColor(sf::Color(255, 255, 255, opasity));
}

void Chip::StopFlicker()
{
	sprite.setColor(original_color);
}


void Chip::update(const float delta_time)
{

}

void Chip::SetTypeOnConstruct(const sf::IntRect& rect)
{
	if (rect.left == 0)
		chip_type = ChipType::Green;
	if (rect.left == 100)
		chip_type = ChipType::Magenta;
	if (rect.left == 200)
		chip_type = ChipType::Blue;
	if (rect.left == 300)
		chip_type = ChipType::Yellow;
	if (rect.left == 400)
		chip_type = ChipType::Red;
	if (rect.left == 500)
		chip_type = ChipType::Black;
	if (rect.left == 600)
		chip_type = ChipType::White;
	if (rect.left == 700)
		chip_type = ChipType::Orange;
	if (rect.left == 800)
		chip_type = ChipType::Cyan;
}