#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "parameter.h"

#ifndef _Pixel_
#define _Pixel_
class Pixel{
public:
    Pixel() = default;
    void init();
    void setColorWithType(std::string setcolor, std::string settype);
    void move(std::string action);
    void drop();
    void rotate();
    void updateRealCoordinate();
    void recordState();
    void releaseState();
    bool check_x();
    bool check_y();
    std::pair<int, int> getCord(int i);
    std::pair<int, int> getColor();
    int searchColorIndex();
    void debug();

private:
    int color_x, color_y;
    int Cord[4][2];
    int Cord_pre[4][2];
    int figure[4];
    int drop_y = 0, move_x = 0;
    bool rot = false;
};
#endif