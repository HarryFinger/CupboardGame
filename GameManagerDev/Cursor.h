#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Cursor: public sf::Drawable
{
public:
	Cursor(const std::string& path);
	void setMouseXY(float x, float y)
	{
		mouse_x = x;
		mouse_y = y;
		//update sprite position
		cursor_sprite.setPosition(x, y);
		cir_shape.setPosition(x, y);
	}
	
	sf::Sprite getCursorSprite();
	sf::CircleShape getCirShape();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Texture cursor_texture;
	sf::Sprite cursor_sprite;
	sf::CircleShape cir_shape;
	float mouse_x;
	float mouse_y;
};

