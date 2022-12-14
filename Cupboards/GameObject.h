#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class GameObject : public sf::Drawable
{
public:
	GameObject(const sf::IntRect& rect, const sf::Vector2f& position, const std::string& path);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(const sf::Vector2f& vec);
	bool IsContains(const sf::Vector2f& vec);
	sf::Sprite GetSprite() { return sprite;}
	sf::Vector2f getPosition() const { return sprite.getPosition(); }
	virtual ~GameObject() = 0;
	
protected:
	sf::Texture texture;
	sf::Sprite sprite;
};

