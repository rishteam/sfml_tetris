#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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
    24, 8
};

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

class Pixel{

public:
    void setColorWithType(std::string setcolor, std::string settype)
    {
        std::string color[8] = {"Blue", "Green", "Red", "Purple", "Garbage", "Brown", "Yellow", "Gray"};
        std::string type[7] = {"I", "Z", "S", "T", "L", "J", "O"};
        for(int i = 0; i < 8; i++)
        {
            if (color[i] == setcolor)
            {
                color_x = pixel_unit[i][0];
                color_y = pixel_unit[i][1];
            }
        }

        for(int i = 0; i < 7; i++)
            if(type[i] == settype)
                for(int j = 0; j < 4; j++)
                    figure[j] = figures[i][j];
    }

    void setRealCoordinate()
    {
        for (int i = 0; i < 4; i++)
        {
            RenderCord[i][0] = figure[i] / 2;
            RenderCord[i][1] = figure[i] % 2;
        }
    }

    void draw(sf::Sprite tiles, sf::RenderWindow *window)
    {
        for (int i = 0; i < 4; i++)
        {
            // std::cout << i << ":" << RenderCord[i][0] << " " << RenderCord[i][1] << '\n';
            tiles.setTextureRect(sf::IntRect(color_x, color_y, 8, 8));
            tiles.setPosition(RenderCord[i][1]*40, RenderCord[i][0]*40);
            tiles.setScale(5.f, 5.f);
            window->draw(tiles);
        }
    }


private:
    int color_x, color_y;
    int RenderCord[4][2];
    int figure[4];
};

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display
    // img: https://opengameart.org/art-search?keys=tetris
    sf::Texture t1, t2, t3;
    t1.loadFromFile("./src/img/8_bit_tetris_pixel.png");

    sf::Sprite tiles(t1);

    sf::Clock clock;
    float timer = 0, delay = 1.0;

    while (window.isOpen())
    {
        float unit_time = clock.getElapsedTime().asSeconds();
        timer += unit_time;

        // Process events
        sf::Event event;

        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //time handler
        // if( timer > delay)
        // {
        //     if(Counter >= 7)
        //         Counter %= 7;
        //     else
        //         Counter++;
        //     timer = 0;
        // }

        //render pixel
        Pixel blue_I;
        blue_I.setColorWithType("Blue","I");
        blue_I.setRealCoordinate();
        window.clear(sf::Color::White);
        blue_I.draw(tiles, &window);

        window.display();
    }
    return EXIT_SUCCESS;
}