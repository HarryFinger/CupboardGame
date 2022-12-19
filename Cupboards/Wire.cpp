#include "Wire.h"

Wire::Wire(const sf::IntRect &rect, const sf::Vector2f &position, const std::string &path)
    : GameObject(rect, position, path)
{
    SetTypeOnConstruct(rect);
}

void Wire::SetTypeOnConstruct(const sf::IntRect &rect)
{
    if (rect.left == 0)
    {
        path_type = WireType::Horisontal;
    }

    if (rect.left == 0)
    {
        path_type = WireType::Vertical;
    }
}
