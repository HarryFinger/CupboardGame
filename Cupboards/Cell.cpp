#include "Cell.h"

namespace
{
	const uint32_t MODULE = 100;
}

Cell::Cell(const sf::IntRect& rect, const sf::Vector2f& position, const std::string& path)
	: GameObject(rect, position, path){}

void Cell::ChangeFrameView(const FrameType& frame_type)
{
	switch (frame_type)
	{
	case FrameType::Green:
	{
		this->frame_type = FrameType::Green;
		sprite.setTextureRect(sf::IntRect(0, 0, MODULE, MODULE));
	}
		break;
	case FrameType::Yellow:
	{
		this->frame_type = FrameType::Yellow;
		sprite.setTextureRect(sf::IntRect(MODULE, 0, MODULE, MODULE));
	}
		break;
	}
}

