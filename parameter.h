#pragma once

#define SCORE_POS_X 225
#define SCORE_POS_Y 20
#define BLOOD_POS_X 40
#define BLOOD_POS_Y 20
#define FULL_HP 3
#define EDGE_SIZE 40
#define START_X 200
#define START_Y 40
#define LEFT_LIMIT 40
#define RIGHT_LIMIT 400
#define TOTAL_X 10
#define TOTAL_Y 19
#define BOTTOM_LIMIT 800

static int Counter = 0;
static int pixel_unit[9][2] =
{
    -1, -1,
    0, 0,
    8, 0,
    16, 0,
    24, 0,
    0, 8,
    8, 8,
    16, 8,
    24, 8
};

/*
1 2
3 4
5 6
7 8
*/

static int figures[7][4] =
{
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
};

static std::string color[9] = {"", "Blue", "Green", "Red", "Purple", "Garbage", "Brown", "Yellow", "Gray"};
static std::string type[7] = {"I", "Z", "S", "T", "L", "J", "O"};
