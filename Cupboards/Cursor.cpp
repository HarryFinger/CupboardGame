#include "Cursor.h"

namespace
{
constexpr float CURSOR_SCALE = 0.27f;
}

Cursor::Cursor(const std::string &path)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 250, 250));
    sprite.setScale(CURSOR_SCALE, CURSOR_SCALE);
    sf::Mouse mouse;
    sprite.setPosition(static_cast<float>(mouse.getPosition().x), static_cast<float>(mouse.getPosition().y));

    sprite.setOrigin(30.f, 30.f);
    original_scale = sprite.getScale();
}

sf::Sprite Cursor::getCursorSprite() const
{
    return sprite;
}

void Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // target.draw(cir_shape);
    target.draw(sprite);
}

void Cursor::update(const float delta_time)
{
    Flicker(delta_time);
}

void Cursor::Flicker(const float delta_time)
{
    time_accumulator += delta_time; // potential inf
    float opasity = (std::sin(time_accumulator * frequency) + 1.f) * scale_ratio + 0.9f;

    sprite.setScale(original_scale.x * opasity, original_scale.y * opasity);
}
