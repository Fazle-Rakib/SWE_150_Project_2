#pragma once
#include <SFML/Graphics.hpp>
class Bomb
{
    public:
    Bomb (float position_x,float position_y);
    ~Bomb();

    void Draw(sf::RenderWindow &window,float position_x,float position_y);

    sf::Texture bombTexture;
    sf::Texture blastTexture;

    sf::Sprite bombSprite;
    sf::Sprite blastSprite;


private:
};
