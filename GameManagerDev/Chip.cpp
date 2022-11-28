#include "Chip.h"

Chip::Chip(const sf::IntRect& rect, const float& X, const float& Y, const std::string& path) :
	GameObject(rect, X, Y, path)
{
	SetTypeOnConstruct(rect);
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
}

