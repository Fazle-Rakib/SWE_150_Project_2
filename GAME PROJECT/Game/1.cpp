#include<SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include "menu.h"
//#include "game.h"
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

vector< pair <int,int> > vect1;
int main()
{
    srand(time(NULL));

    RenderWindow window;
    window.create(VideoMode(925,600),"Bomber Friends");

    //**2**//
    enum Direction{Down,Left,Right,Up};

    sf::Vector2i source(1,Down); // WE can handle source by source.x & source.y

    //window.setKeyRepeatEnabled(false);

    //TEXTURE DECLERATION
    sf::Texture texturePlayer;
    sf::Texture textureFrame;
    sf::Texture textureGrass;
    sf::Texture textureBlock;
    sf::Texture enemy_anime;
    sf::Texture Block_footbe;
    sf::Texture Block_footbe1;

    //LOAD FILE
    texturePlayer.loadFromFile("data/image/kavi.png");
    textureFrame.loadFromFile("data/image/frame1.png");
    textureGrass.loadFromFile("data/image/grass.png");
    enemy_anime.loadFromFile("data/image/death_scythe.png");
    Block_footbe.loadFromFile("data/step0001.png");
    Block_footbe1.loadFromFile("data/image/footbe_type2.png");
    textureBlock.loadFromFile("data/image/block_fix.png");


    sf::Sprite playerImage(texturePlayer); //,sf::IntRect(0,0,35,50)
    sf::Sprite blocki(textureBlock);
    sf::Sprite enemyImage(enemy_anime);
    sf::Sprite frame(textureFrame);
    sf::Sprite grass(textureGrass);
    sf::Sprite block_foot (Block_footbe);
    sf::Sprite block_foot1 (Block_footbe1);

    playerImage.setPosition(186,50);
    enemyImage.setPosition(386,50);
    frame.setPosition(0,0);
    grass.setPosition(125,0);

    ///pixel scale
        blocki.setScale(Vector2f(1.117f,.676f));
        block_foot.setScale(Vector2f(1.15f,.92f));
        block_foot1.setScale(Vector2f(1.21f,.99f));

    ///dataset_array
    int arr1[49]={2,5,8,11   ,1,1,3,3,3,4,4,6,7,7,9,9,10,10,12,12,12,2,2,2,3,4,4,5,5,5,5,6,6,7,7,7,8,9,10,10,11,11,12};
    int arr2[49]={2,4,6,8,10 ,5,8,1,4,6,3,9,5,3,8,3,6,4 ,6 ,1,5 ,8,5,7,3,3,7,8,1,3,5,9,3,4,5,7,9,3,2,9 ,10, 3 ,9  ,4 };
    for(int n=0;n<39;n++)
        {
               vect1.push_back(make_pair(arr1[n],arr2[n]));
        }


    sf::SoundBuffer soundBuffer;
    sf::SoundBuffer menuBuffer;

    sf::Sound gameSound;
    sf::Sound menuSound;

    soundBuffer.loadFromFile("data/music/game.wav");
    menuBuffer.loadFromFile("data/music/menu.wav");

    gameSound.setBuffer(soundBuffer);
    menuSound.setBuffer(menuBuffer);

    menuSound.play();
    menuSound.setLoop(true);


    gameSound.setLoop(true);
    //**2**//

    Menu menu(window.getSize().x,window.getSize().y);

    bool menu1 = true,game = false, gameover = false, Display = false;



    while(window.isOpen())
    {

        Event event;
        if(menu1)
        {
            while(window.pollEvent(event))
            {

                switch(event.type)
                {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        menu.MoveUp();
                        //break;
                    }

                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        menu.MoveDown();
                        //break;
                    }
                    else if(event.key.code == sf::Keyboard::Return)
                    {
                        switch(menu.GetPressedItem())
                        {
                        case 0:
                            cout << "Play button" <<endl;
                            menuSound.pause();
                            gameSound.play();
                            menu1 = false;
                            game = true;
                            gameover = false;
                            break;
                        case 1:
                            cout << "Credit button pressed" << endl;
                            break;
                        case 2:
                            window.close();
                            break;
                        }
                    }
                    break;
                }
            }
            sf::Event::MouseMoved;
                        //cout << event.mouseMove.x << " " << event.mouseMove.y << endl;
                        if((event.mouseMove.x >= 200 && event.mouseMove.x <= 600) && (event.mouseMove.y >= 50 && event.mouseMove.y <= 250)) //(360,160),(575,175)
                        {
                            menu.Mouse1();
                            if(Mouse::isButtonPressed(Mouse::Left))
                            {
                            cout << "Play button" <<endl;
                            menuSound.pause();
                            gameSound.play();
                            menu1 = false;
                            game = true;
                            gameover = false;
                            }

                        }
                        else if((event.mouseMove.x >= 400 && event.mouseMove.x <= 500) && (event.mouseMove.y >= 305 && event.mouseMove.y <= 325)) //(400,305),(500,325)
                        {
                            menu.Mouse2();
                            if(Mouse::isButtonPressed(Mouse::Left))
                            {
                                cout << "Credit button pressed" << endl;
                            }

                        }
                        else if((event.mouseMove.x >= 400 && event.mouseMove.x <= 500) && (event.mouseMove.y >= 430 && event.mouseMove.y <= 500))//(420,455),(485,475)
                        {
                            menu.Mouse3();
                            if(Mouse::isButtonPressed(Mouse::Left))
                            {
                                window.close();
                            }
                        }
                    /*if(event.mouseButton.button == Mouse::Right)
                    {
                            menuSound.pause();
                            gameSound.play();
                            menu1 = false;
                            game = true;
                            gameover = false;
                    }*/
                    //break;

                menu.draw(window);

                window.display();

                window.clear();
            }

        if(game)
        {
            window.clear();
            Display = true;
            if(Keyboard::isKeyPressed(Keyboard::Escape) && game == true)
            {
                menu1 = true;
                game = false;
                gameover = false;
                Display = false;
                gameSound.pause();
                menuSound.play();
                playerImage.setPosition(186,50);
                window.clear();
                //return;
            }
            //Event event;



            while(window.pollEvent(event))
            {
                if(Display)
                {
                     ///player_move
                        source.x++;
                        if(source.x*32 >= texturePlayer.getSize().x)
                        source.x = 0;
                        window.draw(frame);
                        window.draw(grass);
                        playerImage.setTextureRect(IntRect(source.x * 32,source.y * 48,32,48));

                        ///fix block
                        for(int column=1;column<=4;column++)
                        {
                            for(int row=1;row<=5;row++)
                            {
                                int x=125+vect1[column-1].first*57;
                                int y=vect1[row-1].second*50;
                                blocki.setPosition(x,y);
                                window.draw(blocki);
                            }
                        }

                        ///foota block
                        int j=4;
                        while(j<=vect1.size())
                        {
                        int xf=vect1[j].first*57+125;
                        int yf= vect1[j+1].second*50;
                        block_foot.setPosition(xf,yf);
                        block_foot1.setPosition(xf,yf);

                        if(j<21)
                            window.draw(block_foot);

                        else
                            window.draw(block_foot1);
                        j++;
                            window.draw(playerImage);

                        }
                        window.display();
                        window.clear();
                }

                switch(event.type)
                {
                case Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    //if(event.key.code == sf::Keyboard::Up)
                     //   sound.play();
                    if(event.key.code == sf::Keyboard::Down){
                        source.y = Down;
                        playerImage.move(0,10);
                    }
                    else if(event.key.code == sf::Keyboard::Left){
                        source.y = Left;
                        playerImage.move(-10,0);
                    }
                    else if(event.key.code == sf::Keyboard::Right){
                        source.y = Right;
                        playerImage.move(+10,0);
                    }
                    else if(event.key.code == sf::Keyboard::Up){
                        source.y = Up;
                        playerImage.move(0,-10);
                    }
                    else if(event.key.code == sf::Keyboard::Escape)
                    {
                        game = false;
                        gameover = false;
                        Display = false;
                        gameSound.pause();
                        menuSound.play();
                        //return;
                    }
                        break;
                }


        }
     }

    }
}



