#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Cursor.h"
#include "Manager.h"

namespace
{
constexpr float FPS = 1.f / 60.f;
constexpr uint32_t WINDOW_SIZE = 1000;

} // namespace

#ifdef GAME_DEBUG
int main()
#endif

#ifdef RELEASE
    int WinMain()
#endif
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Cupboards Game",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setMouseCursorVisible(0);
    Manager manager;

    sf::Clock main_clock;
    float prev_time = main_clock.getElapsedTime().asSeconds();
    float time_accumulator = FPS;

    // std::ofstream log_file("./data/log.txt");

    while (window.isOpen())
    {
        // loop time calculation
        float current_time = main_clock.getElapsedTime().asSeconds();
        float loop_time = current_time - prev_time;
        time_accumulator += loop_time;

        prev_time = current_time;

        /*if (time_accumulator >= FPS)*/
        while (time_accumulator >= FPS)
        {
            // event state
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                manager.processInput(event);
            }

            // update state
            manager.update(FPS);

            // render state
            window.clear();
            manager.render(window);

            window.display();
            time_accumulator -= FPS;
        }
    }

    return 0;
}