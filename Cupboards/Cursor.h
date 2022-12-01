#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Cursor final : public sf::Drawable
{
public:
	Cursor(const std::string& path);

	void setMouseXY(float x, float y);
	sf::Sprite getCursorSprite();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const float delta_time);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::CircleShape cir_shape;
	float mouse_x;
	float mouse_y;

	sf::Vector2f original_scale;
	float scale_ratio = 0.03f;
	float time_accumulator = 0;
	float frequency = 5;

private:
	void Flicker(const float delta_time);
};

