#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class GameObject : public sf::Drawable
{
public:
	GameObject(const sf::IntRect& rect,
			const float& X, const float& Y, const std::string& path);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setObjectXY(const float& X, const float& Y);
	bool IsContains(float X, float Y);
	float getX() { return X_; }
	float getY() { return Y_; }
	
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	float X_;
	float Y_;
};

