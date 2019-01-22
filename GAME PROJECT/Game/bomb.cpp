#include "bomb.h"
#include <iostream>
#include <bits/stdc++.h>
bool blast = false;
bool bomb = true;


Bomb::Bomb(float position_x,float position_y)
{
    std::cout << position_x << " "  << position_y << std::endl;
    bombTexture.loadFromFile("data/bombSprite.png");
    blastTexture.loadFromFile("data/image/Explosion03.png");

    bombSprite.setTexture(bombTexture);
    blastSprite.setTexture(blastTexture);




}
Bomb::~Bomb()
{

}
void Bomb::Draw(sf::RenderWindow &window,float position_x,float position_y)
{
    sf::Clock clock;
    sf::Time bombElapse = clock.getElapsedTime();

    bombSprite.setPosition(position_x*32,position_y*48);
    blastSprite.setPosition(position_x*32,position_y*48);
    bombSprite.setScale(.03417f,.0298f);
    std::cout << position_x << " "  << position_y << std::endl;
    if(bombElapse.asMilliseconds() == 3500)
    {
        blast=true;
        bomb = false;
        window.draw(blastSprite);
        // clock.restart();
    }


    if( bomb)
    {
        window.draw(bombSprite);
    }
}

