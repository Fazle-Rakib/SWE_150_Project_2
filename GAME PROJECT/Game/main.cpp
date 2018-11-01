#include<SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
int main()
{
    enum Direction{Down,Left,Right,Up};

    sf::Vector2i source(1,Down); // WE can handle source by source.x & source.y

    sf::RenderWindow window;
    window.create(sf::VideoMode(925,600),"Bomber Friends");

    //window.setKeyRepeatEnabled(false);

    sf::Texture textureFrame;
    sf::Texture texture;
    sf::Texture textureGrass;


    textureFrame.loadFromFile("data/image/frame1.png");
    texture.loadFromFile("data/image/kavi.png");
    textureGrass.loadFromFile("data/image/grass.png");


    sf::Sprite frame(textureFrame);
    frame.setPosition(0,0);
    sf::Sprite playerImage(texture); //,sf::IntRect(0,0,35,50)
    playerImage.setPosition(186,50);
    sf::Sprite grass(textureGrass);
    grass.setPosition(125,0);


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
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Down){
                    source.y = Down;
                    playerImage.move(0,5);
                }
                else if(event.key.code == sf::Keyboard::Left){
                    source.y = Left;
                    playerImage.move(-5,0);
                }
                else if(event.key.code == sf::Keyboard::Right){
                    source.y = Right;
                    playerImage.move(+5,0);
                }
                else if(event.key.code == sf::Keyboard::Up){
                    source.y = Up;
                    playerImage.move(0,-5);
                }
                    break;
            }
            source.x++;
            if(source.x*32 >= texture.getSize().x)
                source.x = 0;

            window.draw(frame);

            window.draw(grass);
            playerImage.setTextureRect(sf::IntRect(source.x * 32,source.y * 48,32,48));
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
