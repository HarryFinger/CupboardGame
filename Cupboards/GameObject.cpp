#include "GameObject.h"

GameObject::GameObject(const sf::IntRect &rect, const sf::Vector2f &position, const std::string &path)
{
    sprite.setPosition(position);
    texture.loadFromFile(path);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setOrigin(static_cast<float>(rect.width / 2), static_cast<float>(rect.height / 2));
}

void GameObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
}

void GameObject::setPosition(const sf::Vector2f &vec)
{
    sprite.setPosition(vec);
}

bool GameObject::IsContains(const sf::Vector2f &vec) const
{
    return (sprite.getGlobalBounds().contains(vec));
}

GameObject::~GameObject()
{
}
