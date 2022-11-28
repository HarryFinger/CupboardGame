#include "GameObject.h"

GameObject::GameObject(const sf::IntRect& rect,
				const float& X, const float& Y, const std::string& path): X_(X), Y_(Y)
{
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.setOrigin(static_cast<float>(rect.width / 2), static_cast<float>(rect.height / 2));
	sprite.setPosition(X,Y);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void GameObject::setObjectXY(const float& X, const float& Y)
{
	X_ = X;
	Y_ = Y;
	sprite.setPosition(X_, Y_);
}

bool GameObject::IsContains(float X, float Y)
{
	return (sprite.getGlobalBounds().contains(X, Y));
}