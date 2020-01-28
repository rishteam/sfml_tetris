#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "parameter.h"
#include "canvas.h"
#include "pixel.h"

void pixel_init(Pixel *pixel)
{
    pixel->init();
    srand(time(NULL));
    int color_idx = rand() % 8;
    srand(time(NULL));
    int type_idx = rand() % 7;
    pixel->setColorWithType(color[color_idx], type[type_idx]);
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML window");
    Canvas canvas;
    sf::Clock clock;
    Pixel pixel;
    float timer = 0, delay = 0.4;
    pixel_init(&pixel);

    while (window.isOpen())
    {
        //time setting
        float unit_time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += unit_time;

        // Process events
        sf::Event event;

        // Key pressed
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            // Key Event
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Left)
                    pixel.move("LEFT");
                else if (event.key.code == sf::Keyboard::Right)
                    pixel.move("RIGHT");
                else if (event.key.code == sf::Keyboard::Up)
                    pixel.rotate();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;

        // time handler
        if (timer > delay)
        {
            pixel.recordState();
            pixel.drop();
            pixel.updateRealCoordinate();
            if (!pixel.check_x())
            {
                pixel.releaseState();
            }
            if(!pixel.check_y() || !canvas.collision(pixel))
            {
                pixel.releaseState();
                if (!canvas.collision(pixel))
                    canvas.clear();
                else
                    canvas.putCanvas(pixel);
                //clear state
                pixel_init(&pixel);
            }
            timer = 0;
        }

        delay = 0.4;
        window.clear(sf::Color::White);
        canvas.clearLine();
        canvas.setCanvas(&window);
        canvas.drawExist(&window);
        canvas.drawPixel(pixel, &window);

        window.display();
    }
    return EXIT_SUCCESS;
}