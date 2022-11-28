#include "Wire.h"
Wire::Wire(const sf::IntRect& rect, const float& X, const float& Y, const std::string& path) :
	GameObject( rect, X, Y, path)
{
	SetTypeOnConstruct(rect);
}

void Wire::SetTypeOnConstruct(const sf::IntRect& rect)
{
	if (rect.left == 0)
		path_type = WireType::Horisontal;
	if (rect.left == 0)
		path_type = WireType::Vertical;
}
