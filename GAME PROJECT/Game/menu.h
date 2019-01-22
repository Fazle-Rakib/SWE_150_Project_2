#pragma once
#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 4
#include<iostream>
using namespace sf;
using namespace std;
class Menu
{
public:
    Menu (float width,float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void MouseInput();
    void MoveUp();
    void MoveDown();
    void Mouse1();
    void Mouse2();
    void Mouse3();
    int GetPressedItem() {return selectedItemIndex;}

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Texture menuTexture;
        Texture tr_texturu1;
        Texture tr_texturu2;
       Texture tr_texturu3;
       Texture tr_texturu4;
    sf::Sprite menuSprite;
        Sprite menu_tr1;
        Sprite menu_tr2;
        Sprite menu_tr3;
        Sprite menu_tr4;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
};
