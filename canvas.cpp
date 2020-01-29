#include <iostream>
#include <cstring>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "parameter.h"
#include "canvas.h"
#include "pixel.h"

Canvas::Canvas()
{
    // Load a sprite to display
    // img: https://opengameart.org/art-search?keys=tetris
    t1.loadFromFile("./src/img/8_bit_tetris_pixel.png");
    t2.loadFromFile("./src/img/back.png");
    memset(field,0,sizeof(field));
}

void Canvas::setCanvas(sf::RenderWindow *window)
{
    sf::Sprite background(t2);
    background.setScale(600 / background.getLocalBounds().width, 800 / background.getLocalBounds().height);
    window->draw(background);
}

bool Canvas::collision(Pixel pixel)
{
    for(int k = 0; k < 4; k++)
    {
        for (int i = 0; i < TOTAL_X; i++)
        {
            for (int j = 0; j < TOTAL_Y; j++)
            {
                int x = pixel.getCord(k).first - EDGE_SIZE;
                int y = pixel.getCord(k).second - START_Y;
                if (field[(x / EDGE_SIZE)][y / EDGE_SIZE] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void Canvas::clear()
{
    memset(field,0,sizeof(field));
}

void Canvas::clearLine()
{
    int k = TOTAL_Y-1;
    for (int i = TOTAL_Y - 1; i > 0; i--)
    {
        int count = 0;
        for (int j = 0; j < TOTAL_X; j++)
        {
            if (field[j][i])
                count++;
            field[j][k] = field[j][i];
        }
        if (count < TOTAL_X)
            k--;
    }
}

void Canvas::putCanvas(Pixel pixel)
{
    printf("%d\n",pixel.searchColorIndex());
    printf("%d %d\n", pixel.getColor().first, pixel.getColor().second);
    for (int i = 0; i < 4; i++)
    {
        int x = pixel.getCord(i).first - EDGE_SIZE;
        int y = pixel.getCord(i).second - START_Y;
        field[x / EDGE_SIZE][y / EDGE_SIZE] = pixel.searchColorIndex();
    }
}

void Canvas::drawExist(sf::RenderWindow *window)
{
    sf::Sprite tiles(t1);

    for (int i = 0; i < TOTAL_X; i++)
        for (int j = 0; j < TOTAL_Y; j++)
        {
            if (field[i][j] == 0)
                continue;
            else
            {
                tiles.setTextureRect(sf::IntRect(pixel_unit[field[i][j]][0], pixel_unit[field[i][j]][1], 8, 8));
                tiles.setPosition(i * EDGE_SIZE + EDGE_SIZE, j * EDGE_SIZE + START_Y);
                tiles.setScale(5.f, 5.f);
                window->draw(tiles);
            }
        }
}

void Canvas::drawPixel(Pixel pixel, sf::RenderWindow *window)
{
    sf::Sprite tiles(t1);
    for (int i = 0; i < 4; i++)
    {
        tiles.setTextureRect(sf::IntRect(pixel.getColor().first, pixel.getColor().second, 8, 8));
        tiles.setPosition(pixel.getCord(i).first, pixel.getCord(i).second);
        tiles.setScale(5.f, 5.f);
        window->draw(tiles);
    }
}

void Canvas::debug()
{
    for (int i = 0; i < TOTAL_Y; i++)
    {
        for (int j = 0; j < TOTAL_X; j++)
        {
            printf("%d ",field[j][i]);
        }
        printf("\n");
    }
    printf("----------\n");
}