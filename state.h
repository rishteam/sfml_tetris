#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class State
{
public:
    State();
    void reset();
    bool gameover();
    void setScore(int score_value);
    int getScore();
    void setHp(int hp_value);
    int getHp();
    void subHp();
    void addHp();

private:
    int score;
    int hp;
};