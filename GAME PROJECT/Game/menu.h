#pragma once
#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 3
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
    sf::Sprite menuSprite;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
};
