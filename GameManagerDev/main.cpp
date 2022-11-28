#include <SFML/Graphics.hpp>
#include <iostream>
#include "Manager.h"
#include "Cursor.h"

const float FPS = 1.f / 30.f;
const uint32_t WINDOW_SIZE = 1000;

int main()
{

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "ProjectX", sf::Style::Titlebar | sf::Style::Close);
    window.setMouseCursorVisible(0);
    Manager manager;

    sf::Clock main_clock;
    float prev_time = main_clock.getElapsedTime().asSeconds();
    float time_accumulator = FPS;

    while (window.isOpen())
    {
        //delta time + fps calculation
        float current_time = main_clock.getElapsedTime().asSeconds();
        float delta_time = current_time - prev_time;
        time_accumulator += delta_time;
        prev_time = current_time;

        if (time_accumulator >= FPS)
        {
            //event state
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                manager.processInput(event);
            }

            //update state
            manager.update(delta_time);

            //render state
            window.clear();
            manager.render(window);

            window.display();
            time_accumulator = 0;
        }
    }

    return 0;
}