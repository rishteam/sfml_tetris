#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "pixel.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML window");
    // Load a sprite to display
    // img: https://opengameart.org/art-search?keys=tetris
    sf::Texture t1, t2, t3;
    t1.loadFromFile("./src/img/8_bit_tetris_pixel.png");
    t2.loadFromFile("./src/img/back.png");
    sf::Sprite tiles(t1), background(t2);

    sf::Clock clock;
    Pixel blue_I;
    float timer = 0, delay = 0.5;

    while (window.isOpen())
    {
        float unit_time = clock.getElapsedTime().asSeconds();
        clock.restart();
        // printf("timer:%d\n",timer);
        timer += unit_time;

        // Process events
        sf::Event event;

        //record state
        blue_I.setColorWithType("Blue", "Z");
        blue_I.updateRealCoordinate();
        if (!blue_I.judge())
            blue_I.releaseState();
        blue_I.recordState();
        //std::cout << "Before" << "\n";

        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            // Key Event
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Left)
                    blue_I.move("LEFT");
                else if (event.key.code == sf::Keyboard::Right)
                    blue_I.move("RIGHT");
                // else if (event.key.code == sf::Keyboard::Left)
                //     blue_I.rotate()
            // if (event.key.code == Keyboard::Up)
            // rotate = true;
        }

        //time handler
        if (timer > delay)
        {
            blue_I.drop();
            timer = 0;
        }
        blue_I.updateRealCoordinate();
        if (!blue_I.judge())
            blue_I.releaseState();

        // blue_I.debug();
        // sf::sleep(sf::seconds(0.5f));
        window.clear(sf::Color::White);
        background.setScale(600 / background.getLocalBounds().width, 800 / background.getLocalBounds().height);
        window.draw(background);

        blue_I.draw(tiles, &window);

        window.display();
    }
    return EXIT_SUCCESS;
}