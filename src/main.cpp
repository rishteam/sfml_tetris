#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "parameter.h"
#include "canvas.h"
#include "state.h"
#include "pixel.h"

void pixel_init(Pixel *pixel)
{
    pixel->init();
    srand(time(NULL));
    int color_idx = rand() % 8 + 1;
    srand(time(NULL));
    int type_idx = rand() % 7;
    pixel->setColorWithType(color[color_idx], type[type_idx]);
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(480, 800), "SFML window");
    sf::Clock clock;
    Canvas canvas;
    Pixel pixel;
    State state;
    float timer = 0, delay = 0.1;
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
            if (!pixel.check_y() || !canvas.collision(pixel))
            {
                pixel.releaseState();
                if (!canvas.collision(pixel))
                {
                    canvas.clear();
                    state.subHp();
                }
                else
                {
                    canvas.putCanvas(pixel);
                }
                pixel_init(&pixel);
            }
            timer = 0;
        }

        delay = 0.4;
        window.clear(sf::Color::White);

        if(state.gameover())
        {
            canvas.setCanvas(&window);
            canvas.drawGameOver(state.getScore(), &window);
            //x:125~350
            //y:400~500
            //y:550~650
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    int x = sf::Mouse::getPosition(window).x;
                    int y = sf::Mouse::getPosition(window).y;
                    if (125 <= x && x <= 350 && 400 <= y && y <= 500)
                    {
                        state.reset();
                        pixel_init(&pixel);
                        canvas.clear();
                        break;
                    }
                    if (125 <= x && x <= 350 && 550 <= y && y <= 650)
                    {
                        window.close();
                    }
                }
            }
        }
        else
        {
            int sc = canvas.clearLine();
            state.setScore(sc + state.getScore());
            canvas.setCanvas(&window);
            canvas.drawExist(&window);
            canvas.drawPixel(pixel, &window);
            canvas.drawScore(state.getScore(), &window);
            canvas.drawHp(state.getHp(), &window);
        }

        window.display();
    }
    return EXIT_SUCCESS;
}