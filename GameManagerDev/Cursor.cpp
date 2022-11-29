#include "Cursor.h"

const float CURSOR_SCALE = 0.27f;

Cursor::Cursor(const std::string& path)
{
	cursor_texture.loadFromFile(path);
	cursor_sprite.setTexture(cursor_texture);
	cursor_sprite.setTextureRect(sf::IntRect(0, 0, 250, 250));
	cursor_sprite.setScale(CURSOR_SCALE, CURSOR_SCALE);
	cursor_sprite.setPosition(500.f, 500.f);
	cursor_sprite.setOrigin(30.f, 30.f);

	const float cir_r = 8.f;
	cir_shape.setRadius(cir_r);
	cir_shape.setFillColor(sf::Color::Magenta);
	cir_shape.setOrigin(cir_r, cir_r);
}

sf::Sprite Cursor::getCursorSprite()
{
	return cursor_sprite;
}

sf::CircleShape Cursor::getCirShape()
{
	return cir_shape;
}

void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(cir_shape);
	target.draw(cursor_sprite);
}
