#include<SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include "menu.h"
//#include "bomb.h"
//#include "game.h"
#include "Collision.h"
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

vector< pair <int,int> > vect1;
int bombNum = 0;
int bombAra[5];
class classBomb
{
public:
    Sprite spriteBomb;
    Sprite spriteExplosion;
    Clock exClock;
    float exTime = 0.0f;
    void initBomb(Texture *texture,Texture *textureBomb)
    {
        exTime = exClock.getElapsedTime().asSeconds();
        spriteBomb.setTexture(*texture);
        spriteBomb.setPosition(-200, -200);

        spriteExplosion.setTexture(*textureBomb);
        spriteExplosion.setScale(0.1689f,0.1451475f);
        //spriteExplosion.setPosition(x-14.25,y-12.5);

    }

    void setPos(int x, int y){
        spriteBomb.setPosition(x, y);
    }
};

int main()
{
    srand(time(NULL));
    RenderWindow window;
    window.create(VideoMode(925,600),"Bomber Friends");
    enum Direction{Down,Left,Right,Up};
    sf::Vector2i source(1,Down);
    ///TEXT
    Text goalTxt,gameovertxt;
    Font goalfont,gameoverfont;

    goalfont.loadFromFile("data/font/Goals.ttf");
    gameoverfont.loadFromFile("data/font/gameover.ttf");

    goalTxt.setFont(goalfont);
    goalTxt.setString("GOALS :");
    goalTxt.setCharacterSize(80);
    goalTxt.setScale(Vector2f(.25,.25));
    goalTxt.setPosition(0.f,60.f);
    goalTxt.setFillColor(Color::Blue);

    ///TEXTURE DECLERATION
    sf::Texture texturePlayer;
    sf::Texture textureFrame;
    sf::Texture textureGrass;
    sf::Texture textureBlock;
    sf::Texture enemy_anime;
    sf::Texture Block_footbe;
    sf::Texture Block_footbe1;
    sf::Texture textureBomb;
    sf::Texture textureExplosion;
    sf::Texture textureHealth;
    sf:;Texture textureKey;
    sf::Texture texturePower;
        Texture player_sole_box;

    ///LOAD FILE
    texturePlayer.loadFromFile("data/image/kavi.png");
    textureFrame.loadFromFile("data/image/frame1.png");
    textureGrass.loadFromFile("data/image/grass.png");
    enemy_anime.loadFromFile("data/image/death_scythe.png");
    Block_footbe.loadFromFile("data/step0001.png");
    Block_footbe1.loadFromFile("data/image/footbe_type2.png");
    textureBlock.loadFromFile("data/image/block_fix.png");
    textureBomb.loadFromFile("data/000.png");
    textureExplosion.loadFromFile("data/explosion/boxAgun.png");
    textureHealth.loadFromFile("data/heart.png");
    textureKey.loadFromFile("data/key.png");
    texturePower.loadFromFile("data/Bolt.png");
    player_sole_box.loadFromFile("data/image/transparent.png");

    ///sprite decl
    sf::Sprite playerImage(texturePlayer); //,sf::IntRect(0,0,35,50)
    sf::Sprite blocki(textureBlock);
    sf::Sprite enemyImage(enemy_anime);
    sf::Sprite frame(textureFrame);
    sf::Sprite grass(textureGrass);
    sf::Sprite block_foot (Block_footbe);
    sf::Sprite block_foot1 (Block_footbe1);
    sf::Sprite spriteHealth(textureHealth);
    sf::Sprite menuKey(textureKey);
    sf::Sprite spritePower(texturePower);
        Sprite transparent_box(player_sole_box);
        //Sprite spriteBomb(textuteBomb);
        //Sprite spriteExplosion(textureExplosion);

    ///Position
    playerImage.setPosition(186,50);
    enemyImage.setPosition(356,50);
    frame.setPosition(0,0);
    grass.setPosition(125,0);
    menuKey.setPosition(0,90);
    spriteHealth.setPosition(0,205);
    spritePower.setPosition(-5,250);

    ///player position detector
    int player_pos_x = 186,player_pos_y = 50;
    int enemy_x = 0,enemy_y = 0;
    int enemyCounter = 0;
    //spriteBomb.setPosition(player_pos_x,player_pos_y);
    //spriteExplosion.setPosition(player_pos_x-14.25,player_pos_y-12.5);

    ///pixel scale
    blocki.setScale(Vector2f(1.117f,.92f));
    block_foot.setScale(Vector2f(1.15f,.92f));
    block_foot1.setScale(Vector2f(1.21f,.99f));
    //spriteExplosion.setScale(0.1689f,0.1451475f);
    spriteHealth.setScale(0.28f,0.28f);
    menuKey.setScale(.546875f,.546875f);
    spritePower.setScale(0.08789f,0.08789f);///.078125(40)
    transparent_box.setScale(Vector2f(0.04f,.019f));
    playerImage.setScale(Vector2f(1.3f,1.2f));

    ///dataset_array
    int arr1[49]={2,5,8,11   ,1,1,3,3,3,4,4,6,7,7,9,9,10,10,12,12,12,2,2,2,3,4,4,5,5,5,5,6,6,7,7,7,8,9,10,10,11,11,12};
    int arr2[49]={2,4,6,8,10 ,5,8,1,4,6,3,9,5,3,8,3,6,4 ,6 ,1,5 ,8,5,7,3,3,7,8,1,3,5,9,3,4,5,7,9,3,2,9 ,10, 3 ,9  ,4 };
    for(int n=0;n<39;n++)
    {
        vect1.push_back(make_pair(arr1[n],arr2[n]));
    }
     ///Time
    vector <Time>explosionTime ;
    explosionTime.clear();

    ///Clock
    sf::Clock explosionClock;
    sf::Clock bombClock[5];
    //std::vector<Clock>explosionClock;

    classBomb vecBomb[5];
    for(int i=0; i<5; i++)
        vecBomb[i].initBomb(&textureBomb,&textureExplosion);

    sf::SoundBuffer soundBuffer;
    sf::SoundBuffer menuBuffer;
    sf::SoundBuffer buttonBuffer;

    sf::Sound gameSound;
    sf::Sound menuSound;
    sf::Sound buttonSound;

    soundBuffer.loadFromFile("data/music/game.wav");
    menuBuffer.loadFromFile("data/music/menu.wav");
    buttonBuffer.loadFromFile("data/music/button1.wav");

    gameSound.setBuffer(soundBuffer);
    menuSound.setBuffer(menuBuffer);
    buttonSound.setBuffer(buttonBuffer);

    buttonSound.setVolume(100);
    menuSound.setVolume(15);

    menuSound.play();
    menuSound.setLoop(true);
    gameSound.setLoop(true);

    Menu menu(window.getSize().x,window.getSize().y);
    bool menu1 = true,game = false, gameover = false, Display = false,bomb1 = false,explosion = false ,gameBack = false,bellExplosion = false,bombBool[5];
    for(int i=0; i<5; i++) bombBool[i]=false;

    ///INITIALIZE
    //int bombNum = 0;
    int f = 1;
    bool colli[4]={false};

    while(window.isOpen())
    {
        Event event;
        if(menu1)
        {
            if(gameBack)
            {
                ///Position
                playerImage.setPosition(186,50);
                enemyImage.setPosition(356,50);
                //grass.setPosition(125,0);
                player_pos_x = 186,player_pos_y = 50;
                int enemy_x = 0,enemy_y = 0;
                int enemyCounter = 0;
                //spriteBomb.setPosition(player_pos_x,player_pos_y);
                //spriteExplosion.setPosition(186,50);
                bombNum = 0;
                //vecBomb[]={0};
                explosionTime.clear();
            }
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
                            buttonSound.play();
                            menu.MoveUp();
                            //break;
                        }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        buttonSound.play();
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
            Event::MouseMoved;
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
                window.clear();
                menu.draw(window);
                window.display();
        }

        if(game)
        {
            Display = true;

            if(Keyboard::isKeyPressed(Keyboard::Escape) && game == true)
            {
                menu1 = true;
                gameBack = true;
                game = false;
                gameover = false;
                Display = false;
                gameSound.pause();
                menuSound.play();
            }
            while(window.pollEvent(event))
            {
                switch(event.type)
                {
                    case Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:

                    if((event.key.code == sf::Keyboard::Down))
                    {
                        if(!(colli[0]))
                        {
                            source.y = Down;
                            playerImage.move(0,+10);
                            player_pos_y+=10;
                        }
                    }
                    else if((event.key.code == sf::Keyboard::Left) )
                    {
                        if(!(colli[1]))
                        {
                            source.y = Left;
                            playerImage.move(-10,0);
                            player_pos_x-=10;
                        }
                    }
                    else if((event.key.code == sf::Keyboard::Right) )
                    {
                        if(!(colli[2]))
                        {
                            source.y = Right;
                            playerImage.move(+10,0);
                            player_pos_x+=10;
                        }
                    }
                    else  if((event.key.code == sf::Keyboard::Up)  )
                    {

                        if(!(colli[3]))
                        {
                            source.y = Up;
                            playerImage.move(0,-10);
                            player_pos_y-=10;
                        }
                    }
                   else if(event.key.code == sf::Keyboard::Escape)
                    {
                        window.clear();
                        game = false;
                        gameover = false;
                        Display = false;
                        gameSound.pause();
                        menuSound.play();

                        //return;
                    }
                   else if(event.key.code == sf::Keyboard::Space)
                     {
                        bombBool[bombNum] = true;
                        bombClock[bombNum].restart();
                        bomb1 = true;
                        vecBomb[bombNum].setPos(player_pos_x,player_pos_y);
                        bombNum = (bombNum+1)%5;
                     }

                        break;
               }
                cout << "X = " << player_pos_x << "\tY = " << player_pos_y << endl;
                source.x++;
                if(source.x*32 >= texturePlayer.getSize().x)
                {
                    source.x = 0;
                }
            }

            if(Display)
            {
             ///player_move
                window.clear();
                window.draw(frame);
                window.draw(grass);
                window.draw(goalTxt);
                window.draw(menuKey);
                window.draw(spritePower);
                window.draw(spriteHealth);
                playerImage.setTextureRect(IntRect(source.x * 32,source.y * 48,32,48));
                enemyImage.setTextureRect(IntRect(enemy_x*50, enemy_y*48, 50, 48));
                transparent_box.setPosition(player_pos_x+8,player_pos_y+48);

                ///ENEMY
                if(enemyCounter == 60)
                {
                    enemy_x = (enemy_x + 1) % 4;
                    enemyCounter = 0;
                }
                enemyCounter++;
                /*
                 if(!enemyImage.getGlobalBounds().intersects(blocki.getGlobalBounds()) || !enemyImage.getGlobalBounds().intersects(block_foot.getGlobalBounds()) || !enemyImage.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                        {
                            enemyImage.move(0,.05);
                        }
                */
                 //enemyImage.move(0,.5);

                for(int a=0;a<=3;a++)
                    colli[a]={false};

                ///fix block
                for(int column=1;column<=4;column++)
                {
                    for(int row=1;row<=5;row++)
                    {

                        int x=125+vect1[column-1].first*57+2;
                        int y=vect1[row-1].second*50-5;
                        blocki.setPosition(x,y);
                        window.draw(blocki);

                        if(transparent_box.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            colli[source.y]=true;

                    }
                }

            ///boundery

                ///upper boundery
                int ubx=67;
                for(int i=0;i<=14;i++)
                {
                    ubx=ubx+57;
                    int y=0;
                    blocki.setPosition(ubx,y);
                    window.draw(blocki);

                    if(transparent_box.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        colli[source.y]=true;
                }
               ///lower boundery
               int dbx=67;
               for(int i=0;i<=14;i++)
                    {
                        dbx=dbx+57;
                        int y=545;
                        blocki.setPosition(dbx,y);

                        window.draw(blocki);

                        if(transparent_box.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            colli[source.y]=true;

                    }

                ///left boundery
               int lby=0;
               for(int i=0;i<=11;i++)
                    {
                        int lbx=125;
                        lby+=50;
                        blocki.setPosition(lbx,lby);

                        window.draw(blocki);

                        if(transparent_box.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           colli[source.y]=true;

                    }
                    ///last left
                        blocki.setPosition(125,545);

                        window.draw(blocki);

                        if(transparent_box.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            colli[source.y]=true;



                ///right boundery
               int rby=0;
               for(int i=0;i<=11;i++)
                    {
                        int rbx=925-57;
                        rby+=50;
                        blocki.setPosition(rbx,rby);

                        window.draw(blocki);

                        if(transparent_box.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            colli[source.y]=true;

                    }
                    ///last left
                        blocki.setPosition(925-57,545);

                        window.draw(blocki);

                        if(transparent_box.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            colli[source.y]=true;


                ///foota block
                int j=4;
                while(j<=vect1.size())
                {
                    int xf=vect1[j].first*57+126;
                    int yf= vect1[j+1].second*50-5;
                    block_foot.setPosition(xf,yf);
                    block_foot1.setPosition(xf,yf);
                    if(j<21)
                    {


                        window.draw(block_foot);

                        if(transparent_box.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                        colli[source.y]=true;

                    }
                    else
                    {

                        window.draw(block_foot1);

                        if(transparent_box.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                        colli[source.y]=true;
                    }
                    j++;
                }
                window.draw(transparent_box);
                window.draw(playerImage);
                if(bomb1)
                {
                    //bomb.Draw(window,player_pos_x,player_pos_y);
                    ///explosionTime = explosionClock.getElapsedTime();
                    ///window.draw(spriteBomb);
                    for(int i = 0; i < 5; i++)
                    {
                        window.draw(vecBomb[i].spriteBomb);
                        explosion = true;
                        bellExplosion = true;

                        if(bombBool[i] == true)
                        {
                            if(bombClock[i].getElapsedTime().asSeconds() >= 5 )
                            {
                                vecBomb[i].setPos(-200,-200);
                                bombBool[i]  = false;
                            }
                        }

                        //explosionTime[i] = explosionClock.getElapsedTime();
                        //cout << explosionTime[i].asSeconds() << endl;
                       /* if(explosionTime[i].asSeconds() > 5)
                        {
                            cout << "BOOOOOOOM" << endl;
                            vecBomb.erase(vecBomb.begin()+i);
                            //explosionClock.restart();

                        }*/


                        /*if(bellExplosion)
                        {
                            explosionClock.restart();
                            bellExplosion  = false;
                        }
                        if(explosion)
                        {
                            if(explosionClock.getElapsedTime().asSeconds() <= .60)
                            {
                                window.draw(vecBomb[i].spriteExplosion);
                            }
                        }*/

                        /*explosionTime[i] = explosionClock[i].getElapsedTime();

                        if(explosionTime[i].asSeconds() >= 3.5)
                        {
                            //spriteBomb.clear();
                            vecBomb.erase(vecBomb.begin()+i);
                            window.draw(spriteExplosion);
                            /*if(explosionTime[i].asSeconds() >= 4.5)
                                explosionClock.restart();}*/

                    }

                    bomb1 == false;
                }

                enemyImage.move(0,.05);
                /*if(Collision::PixelPerfectTest(enemyImage,block_foot1))
                {
                    cout << "collision" << endl;
                }
                else if(Collision::PixelPerfectTest(enemyImage,block_foot))
                {
                    cout << "collision 000)))" << endl;
                }
                else if(Collision::PixelPerfectTest(enemyImage,blocki))
                {
                    cout << "xx collision xx" << endl;
                }
                else if(Collision::PixelPerfectTest(enemyImage,playerImage))
                {
                    cout << "PLAYER collision " << endl;
                }
                else
                {
                    cout << "nnnnnnn" << endl;
                }*/
                    window.display();
            }
        }
    }
}
