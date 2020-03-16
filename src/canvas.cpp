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
    t1.loadFromFile("./img/8_bit_tetris_pixel.png");
    t2.loadFromFile("./img/back.png");
    t3.loadFromFile("./img/quit.png");
    t4.loadFromFile("./img/retry.png");
    memset(field,0,sizeof(field));
}

void Canvas::setCanvas(sf::RenderWindow *window)
{
    sf::Sprite background(t2);
    background.setScale(480 / background.getLocalBounds().width, 800 / background.getLocalBounds().height);
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

int Canvas::clearLine()
{
    int k = TOTAL_Y-1;
    int score_add = 0;
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
        else
            score_add += 1;
    }
    return score_add;
}

void Canvas::putCanvas(Pixel pixel)
{
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

void Canvas::drawScore(int score, sf::RenderWindow *window)
{
    sf::Font font;
    if (font.loadFromFile("./font/slkscr.ttf"))
    {
        sf::Text text;
        text.setFont(font);
        text.setString("Score: " + std::to_string(score));
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::Black);
        text.setPosition(SCORE_POS_X, SCORE_POS_Y);
        window->draw(text);
    }
}

void Canvas::drawHp(int hp, sf::RenderWindow *window)
{
    sf::Sprite FullBlood(t1), LoseBlood(t1);
    FullBlood.setTextureRect(sf::IntRect(40, 0, 8, 8));
    LoseBlood.setTextureRect(sf::IntRect(40, 8, 8, 8));

    for(int i = 0; i < hp; i++)
    {
        FullBlood.setPosition(BLOOD_POS_X + i * EDGE_SIZE, BLOOD_POS_Y);
        FullBlood.setScale(5.f, 5.f);
        window->draw(FullBlood);
    }
    for (int i = hp; i < FULL_HP; i++)
    {
        LoseBlood.setPosition(BLOOD_POS_X + i * EDGE_SIZE, BLOOD_POS_Y);
        LoseBlood.setScale(5.f, 5.f);
        window->draw(LoseBlood);
    }
}

void Canvas::drawGameOver(int score, sf::RenderWindow *window)
{
    sf::Font font;
    sf::Sprite quit(t3), retry(t4);
    //text gameover, score
    if (font.loadFromFile("./font/slkscr.ttf"))
    {
        sf::Text text, text2;
        text.setFont(font);
        text2.setFont(font);
        text.setString("GAME_OVER");
        text2.setString("score:" + std::to_string(score));
        text.setCharacterSize(60);
        text2.setCharacterSize(60);
        text.setFillColor(sf::Color::Red);
        text2.setFillColor(sf::Color::Green);
        text.setPosition(50, 200);
        if(score >= 100)
            text2.setPosition(75, 300);
        else
            text2.setPosition(100, 300);
        window->draw(text);
        window->draw(text2);
    }

    retry.setPosition(125, 400);
    quit.setPosition(125, 550);
    retry.setScale(.25f, .25f);
    quit.setScale(.25f, .25f);
    window->draw(retry);
    window->draw(quit);
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

//FIXME: pixel floating