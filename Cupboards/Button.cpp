#include "Button.h"

Button::Button(const sf::IntRect &rect, const sf::Vector2f &position, const std::string &path)
    : GameObject(rect, position, path)
{
    sprite.setScale(0.95f, 0.95f);
    original_scale = sprite.getScale();
    original_color = sprite.getColor();
}

void Button::Flicker()
{
    sprite.setScale(static_cast<float>(original_scale.x * 1.1f), static_cast<float>(original_scale.y * 1.1f));
    sprite.setColor(sf::Color(222, 222, 255, 255));
}

void Button::StopFlicker()
{
    sprite.setScale(original_scale);
    sprite.setColor(original_color);
}