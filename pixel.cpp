#include <iostream>
#include <cstring>
#include "pixel.h"
#include "canvas.h"
#include "parameter.h"

void Pixel::init()
{
    color_x = 0, color_y = 0;
    memset(Cord, 0, sizeof(Cord));
    memset(Cord_pre, 0, sizeof(Cord_pre));
    memset(figure, 0, sizeof(figure));
    drop_y = 0, move_x = 0;
    rot = false;
}

void Pixel::setColorWithType(std::string setcolor, std::string settype)
{
    for (int i = 0; i < 9; i++)
    {
        if (color[i] == setcolor)
        {
            color_x = pixel_unit[i][0];
            color_y = pixel_unit[i][1];
            printf("set:%d %d\n",color_x,color_y);
        }
    }

    for (int i = 0; i < 7; i++)
        if (type[i] == settype)
            for (int j = 0; j < 4; j++)
                figure[j] = figures[i][j];

    for (int i = 0; i < 4; i++)
    {
        Cord[i][0] = (figure[i] % 2) * EDGE_SIZE + START_X;
        Cord[i][1] = (figure[i] / 2) * EDGE_SIZE + START_Y;
    }
}

void Pixel::updateRealCoordinate()
{
    int mid_ptx = Cord[1][0], mid_pty = Cord[1][1];
    for (int i = 0; i < 4; i++)
    {
        if(rot == false)
        {
            Cord[i][0] = Cord[i][0] + move_x;
            Cord[i][1] = Cord[i][1] + drop_y;
        }
        else
        {
            int x = Cord[i][1] - mid_pty;
            int y = Cord[i][0] - mid_ptx;
            Cord[i][0] = mid_ptx - x;
            Cord[i][1] = mid_pty + y;
        }
    }
    rot = false;
    move_x = 0;
    drop_y = 0;
}

void Pixel::recordState()
{
    for (int i = 0; i < 4; i++)
    {
        Cord_pre[i][0] = Cord[i][0];
        Cord_pre[i][1] = Cord[i][1];
    }
}

void Pixel::releaseState()
{
    for (int i = 0; i < 4; i++)
    {
        Cord[i][0] = Cord_pre[i][0];
        Cord[i][1] = Cord_pre[i][1];
    }
}

void Pixel::drop()
{
    drop_y = EDGE_SIZE;
}

void Pixel::move(std::string action)
{
    if (action == "LEFT")
        move_x = -EDGE_SIZE;
    else if (action == "RIGHT")
        move_x = EDGE_SIZE;
}

void Pixel::rotate()
{
    rot = true;
}

bool Pixel::check_x()
{
    for (int i = 0; i < 4; i++)
    {
        if (Cord[i][0] < LEFT_LIMIT || Cord[i][0] > RIGHT_LIMIT)
            return false;
    }
    return true;
}

bool Pixel::check_y()
{
    for (int i = 0; i < 4; i++)
    {
        if(Cord[i][1] >= BOTTOM_LIMIT)
            return false;
    }
    return true;
}

std::pair<int,int> Pixel::getCord(int i)
{
    auto ret = std::make_pair(Cord[i][0], Cord[i][1]);
    return ret;
}

std::pair<int, int> Pixel::getColor()
{
    auto ret = std::make_pair(color_x, color_y);
    return ret;
}

int Pixel::searchColorIndex()
{
    for(int i = 0; i < 9; i++)
    {
        if (color_x == pixel_unit[i][0] && color_y == pixel_unit[i][1])
            return i;
    }
    return 0;
}

void Pixel::debug()
{
    for (int i = 0; i < 4; i++)
    {
        int x = getCord(i).first - EDGE_SIZE;
        int y = getCord(i).second - START_Y;
        printf("Pixelnow:%d %d\n",(x/EDGE_SIZE), y/EDGE_SIZE);
    }
}
