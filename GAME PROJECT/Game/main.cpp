#include<SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800,600),"Bomber Friends");

    //window.setKeyRepeatEnabled(false);

    sf::Texture textureFrame;
    sf::Texture texture;
    textureFrame.loadFromFile("data/image/frame.png");
    texture.loadFromFile("data/image/char.png");

    sf::Sprite frame(textureFrame);
    frame.setPosition(0,0);
    sf::Sprite playerImage(texture,sf::IntRect(0,0,50,70));
    playerImage.setPosition(0,0);

    /*sf::Font font;
    if(!font.loadFromFile("data/font/ALGER.TTF"))
    {
        std::cout << "Error couldn't load text" << std::endl;
    }
    sf::Text text("GAME OVER", font, 64);
    text.setColor(sf::Color::Red);

    sf::FloatRect bounds(text.getLocalBounds());    ////SET THE POSITION
    text.setPosition(window.getSize().x/2-(bounds.left+bounds.width/2) ,window.getSize().y/2-(bounds.top+bounds.height/2));*/

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
               case sf::Event::Closed:
                window.close();
                break;
            }
            switch(event.type)
            {
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Left)
                    playerImage.move(-5,0);
                if(event.key.code == sf::Keyboard::Right)
                    playerImage.move(5,0);
                if(event.key.code == sf::Keyboard::Up)
                    playerImage.move(0,-5);
                if(event.key.code == sf::Keyboard::Down)
                    playerImage.move(0,5);


            }
            window.draw(frame);
            window.draw(playerImage);
            window.display();
            window.clear();
        }

    }
}

    /*if(!)
    {
        std::cout << "Error couldn't load player image" << std::endl;
    }*/

    //playerImage.setTexture(pTexture);

    /*sf::Vector2u Size(700,500);//SET THE SIZE OF GAMING WINDOW

   // std::cout << Size.x << " " << Size.y << std::endl;
    window.setSize(Size);
    window.setPosition(sf::Vector2i(300,100));   */  //SET THE POSITION OF GAMING WINDOW
