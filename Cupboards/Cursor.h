#pragma once
#include <SFML/Graphics.hpp>

class Cursor final : public sf::Drawable
{
public:
    Cursor(const std::string &path);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(const float delta_time);

    sf::Sprite getCursorSprite() const;

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    void setPosition(const sf::Vector2f &position)
    {
        sprite.setPosition(position);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f original_scale;
    float scale_ratio = 0.03f;
    float time_accumulator = 0;
    float frequency = 5;

private:
    void Flicker(const float delta_time);
};
