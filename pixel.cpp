#include "pixel.h"
#include "parameter.h"
#include <iostream>

int Counter = 0;
int pixel_unit[8][2] =
    {
        0, 0,
        8, 0,
        16, 0,
        24, 0,
        0, 8,
        8, 8,
        16, 8,
        24, 8};

/*
1 2
3 4
5 6
7 8
*/

int figures[7][4] =
    {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // Z
        3, 5, 4, 6, // S
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5, // O
};


void Pixel::setColorWithType(std::string setcolor, std::string settype)
{
    std::string color[8] = {"Blue", "Green", "Red", "Purple", "Garbage", "Brown", "Yellow", "Gray"};
    std::string type[7] = {"I", "Z", "S", "T", "L", "J", "O"};
    for (int i = 0; i < 8; i++)
    {
        if (color[i] == setcolor)
        {
            color_x = pixel_unit[i][0];
            color_y = pixel_unit[i][1];
        }
    }

    for (int i = 0; i < 7; i++)
        if (type[i] == settype)
            for (int j = 0; j < 4; j++)
                figure[j] = figures[i][j];
}

void Pixel::updateRealCoordinate()
{
    for (int i = 0; i < 4; i++)
    {
        Cord[i][0] = (figure[i] % 2) * EDGE_SIZE + move_x;
        Cord[i][1] = (figure[i] / 2) * EDGE_SIZE + drop_y;
    }
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
    }

    for (int i = 0; i < 4; i++)
    {
        bool check = false;
        if (Cord[i][1] >= BOTTOM_LIMIT)
        {
            for (int j = 0; j < 4; j++)
                Cord[j][1] = Cord_pre[j][1];
        }
        if(check)
            break;
    }
}

void Pixel::drop()
{
    drop_y += EDGE_SIZE;
}

void Pixel::move(std::string action)
{
    if (action == "LEFT")
        move_x -= EDGE_SIZE;
    else if (action == "RIGHT")
        move_x += EDGE_SIZE;
}

bool Pixel::judge()
{
    for (int i = 0; i < 4; i++)
    {
        if (Cord[i][0] < LEFT_LIMIT || Cord[i][0] > RIGHT_LIMIT || Cord[i][1] > BOTTOM_LIMIT)
            return false;
    }
    return true;
}

void Pixel::draw(sf::Sprite tiles, sf::RenderWindow *window)
{
    for (int i = 0; i < 4; i++)
    {
        // std::cout << i << ":" << Cord[i][0] << " " << Cord[i][1] << '\n';
        tiles.setTextureRect(sf ::IntRect(color_x, color_y, 8, 8));
        tiles.setPosition(Cord[i][0], Cord[i][1]);
        tiles.setScale(5.f, 5.f);
        window->draw(tiles);
    }
}
void Pixel::debug()
{
    for (int i = 0; i < 4; i++)
    {
        printf("pre:%d: %d %d\n", i, Cord_pre[i][0], Cord_pre[i][1]);
        printf("cord:%d: %d %d\n", i, Cord[i][0], Cord[i][1]);
    }
}