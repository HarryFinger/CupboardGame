#pragma once
#include "GameObject.h"

static const std::string DEFAULT_WIRES_PATH = "./data/GameState/wires.png";

enum class WireType
{
    Horisontal,
    Vertical
};

class Wire final : public GameObject
{
public:
    Wire(const sf::IntRect &rect, const sf::Vector2f &position, const std::string &path = DEFAULT_WIRES_PATH);

private:
    void SetTypeOnConstruct(const sf::IntRect &rect);
    WireType path_type;
};
