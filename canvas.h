#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "pixel.h"


class Canvas
{
public:
    Canvas();
    void setCanvas(sf::RenderWindow *window);
    bool collision(Pixel pixel);
    void clear();
    int clearLine();
    void putCanvas(Pixel pixel);
    void drawExist(sf::RenderWindow *window);
    void drawPixel(Pixel pixel, sf::RenderWindow *window);
    void drawScore(int score, sf::RenderWindow *window);
    void drawHp(int hp, sf::RenderWindow *window);
    void drawGameOver(int score, sf::RenderWindow *window);
    void debug();

private:
    int field[TOTAL_X][TOTAL_Y];
    sf::Texture t1, t2, t3, t4;
};


