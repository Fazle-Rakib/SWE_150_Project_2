#include "menu.h"


Menu::Menu(float width,float height)
{
    menuTexture.loadFromFile("data/menu.png");
    tr_texturu1.loadFromFile("data/image/Game_upor1.2.png");
    tr_texturu2.loadFromFile("data/image/Game_upor1.2.png");
    tr_texturu3.loadFromFile("data/image/Game_upor1.2.png");
    tr_texturu4.loadFromFile("data/image/Game_upor1.2.png");
    menuSprite.setTexture(menuTexture);
    menu_tr1.setTexture(tr_texturu1);
    menu_tr2.setTexture(tr_texturu2);
    menu_tr3.setTexture(tr_texturu3);
    menu_tr4.setTexture(tr_texturu4);
   // menuSprite();
    //menuSprite(menuTexture);
    if(!font.loadFromFile("font1.ttf"))
    {
        //handle error
    }

    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setCharacterSize(35);
    menu[0].setString("Single Player");
    menu[0].setPosition(sf::Vector2f(width / 2+170,height /(MAX_NUMBER_OF_ITEMS+1) *1 ));
    menu_tr1.setPosition(sf::Vector2f(width / 2+120,height /(MAX_NUMBER_OF_ITEMS+1) *1-15));
    menu_tr1.setScale(.7f,0.9f);
    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setCharacterSize(35);
    menu[1].setString("Instruction");
    menu[1].setPosition(sf::Vector2f(width / 2+195,height /(MAX_NUMBER_OF_ITEMS+1) *2));
    menu_tr4.setPosition(sf::Vector2f(width / 2+150,height /(MAX_NUMBER_OF_ITEMS+1) *2-15));
    menu_tr4.setScale(0.6f,0.9f);

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setCharacterSize(35);
    menu[2].setString("Credit");
    menu[2].setPosition(sf::Vector2f(width / 2+210,height /(MAX_NUMBER_OF_ITEMS+1) *3));
    menu_tr2.setPosition(sf::Vector2f(width / 2+170,height /(MAX_NUMBER_OF_ITEMS+1) *3-15));
    menu_tr2.setScale(.4f,0.9f);

    menu[3].setFont(font);
    menu[3].setColor(sf::Color::White);
    menu[3].setCharacterSize(35);
    menu[3].setString("Exit");
    menu[3].setPosition(sf::Vector2f(width / 2+230,height /(MAX_NUMBER_OF_ITEMS+1) *4));
    menu_tr3.setPosition(sf::Vector2f(width / 2+190,height /(MAX_NUMBER_OF_ITEMS+1) *4-15));
    menu_tr3.setScale(.3f,0.9f);

    selectedItemIndex = 0;
}
Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow &window)
{

    window.draw(menuSprite);
    if( selectedItemIndex ==0)
    window.draw(menu_tr1);
    if( selectedItemIndex == 2)
    window.draw(menu_tr2);
    if( selectedItemIndex ==3)
    window.draw(menu_tr3);
    if(selectedItemIndex==1)
    window.draw(menu_tr4);
    for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }

}

void Menu::MoveUp()
{
    if(selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setColor((sf::Color::White));
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setColor((sf::Color::White));
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}
void Menu::Mouse1()
{
    menu[0].setColor(sf::Color::Red);
    menu[1].setColor(sf::Color::White);
    menu[2].setColor(sf::Color::White);
}
void Menu::Mouse2()
{
    menu[1].setColor(sf::Color::Red);
    menu[0].setColor(sf::Color::White);
    menu[2].setColor(sf::Color::White);
}
void Menu::Mouse3()
{
    menu[2].setColor(sf::Color::Red);
    menu[0].setColor(sf::Color::White);
    menu[1].setColor(sf::Color::White);
}

