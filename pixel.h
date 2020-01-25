#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "parameter.h"

class Pixel{
public:
    Pixel() = default;
    void setColorWithType(std::string setcolor, std::string settype);
    void updateRealCoordinate();
    void recordState();
    void releaseState();
    void drop();
    void move(std::string action);
    bool judge();
    void draw(sf::Sprite tiles, sf::RenderWindow *window);
    void debug();

private:
    int color_x, color_y;
    int Cord[4][2];
    int Cord_pre[4][2];
    int figure[4];
    int drop_y = START_Y, move_x = START_X;
};