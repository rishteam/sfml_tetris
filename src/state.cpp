#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "state.h"

State::State()
{
    score = 0;
    hp = 3;
}

void State::reset()
{
    score = 0;
    hp = 3;
}

bool State::gameover()
{
    if(hp <= 0)
        return true;
    else
        return false;
}

void State::setScore(int score_value)
{
    score = score_value;
}

int State::getScore()
{
    return score;
}

void State::setHp(int hp_value)
{
    hp = hp_value;
}

int State::getHp()
{
    return hp;
}

void State::subHp()
{
    hp -= 1;
}

void State::addHp()
{
    hp += 1;
}

