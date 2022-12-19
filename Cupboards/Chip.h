#pragma once
#include "GameObject.h"

namespace
{
const std::string DEFAULT_CHIP_PATH = "./data/GameState/chips.png";

}

class Chip final : public GameObject
{
public:
    Chip(const sf::IntRect &rect, const sf::Vector2f &position, const std::string &path = DEFAULT_CHIP_PATH);
    void Flicker(float delta_time);
    void StopFlicker();
    void update(const float delta_time);

    enum class ChipType
    {
        Green,
        Magenta,
        Blue,
        Yellow,
        Red,
        Black,
        White,
        Orange,
        Cyan
    };

private:
    void SetTypeOnConstruct(const sf::IntRect &rect);

private:
    sf::Vector2f original_scale;
    sf::Color original_color;
    ChipType chip_type;

    float time_accumulator = 0;
    float frequency = 8;
};
