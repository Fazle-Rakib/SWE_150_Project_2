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

vector< pair <int,int> > vect1,vect2;
vector<int>block_blast_pos_x,block_blast_pos_y;
int bombNum = 0;
int bombAra[5];
int pos=0;
int i0,he_sprite_num=1;
int heart_sprite_num=1;
int levelCheck = 0;
bool l1=false,l2=false,l3=false,l0=false;
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
        spriteExplosion.setPosition(-150,-150);
        //spriteExplosion.setPosition(x-14.25,y-12.5);

    }

    void setPos(int x, int y){
        int p1 = x-129,p2 = y-50;
        p1 = p1%57;
        p2 = p2%50;
        if(p1 > 33)
        {
            x = x+(57 - p1-3);
        }
        else
        {
            x = x - p1-3;
        }
        if(p2 > 23)
        {
            y = y+(50 - p2-7);
        }
        else
        {
            y = y - p2-7;
        }
        spriteBomb.setPosition(x, y);
    }
    void setExpl(int x,int y)
    {
        int p1 = x-129,p2 = y-50;
        p1 = p1%57;
        p2 = p2%50;
        if(p1 > 33)
        {
            x = x+(57 - p1-3);
        }
        else
        {
            x = x - p1-3;
        }
        if(p2 > 23)
        {
            y = y+(50 - p2-7);
        }
        else
        {
            y = y - p2-7;
        }
         spriteExplosion.setPosition(x-14.25,y-12.5);
    }
};
std::string To_string(int n)        ///****///
  {
     std::string s="";
     if(n==0)return "0";
     while(n)
     {
       s+=(n%10+'0');
       n/=10;
     }
    reverse(s.begin(),s.end());
     return s;
}


int main()
{

    srand(time(NULL));
    RenderWindow window;

    window.create(VideoMode(925,600),"Bomber Friends");
    //window.setFramerateLimit(20);
    enum Direction{Down,Left,Right,Up};
    sf::Vector2i player(1,Down);
        Vector2i devil_dir(1,Down);
        Vector2i hulk_dir(1,Down);
        Vector2i death_scythe_dir(1,Down);
        Vector2i redskull_dir(1,Left);
        Vector2i explosionVec(1,Down);

        float devil_dir_x=0,devil_dir_y=.3;
        float hulk_dir_x=0,hulk_dir_y=.3;
        float death_scythe_dir_x=0,death_scythe_dir_y=.3;
        float redskull_dir_x=-.4,redskull_dir_y=0;

    Text goalTxt,gameovertxt,playerLifeTxt,playerPowerTxt,keyText,menuGoalText,buttonTxt,pressTxt;
    Font goalfont,gameoverfont,playerfont,keyFont,menuGoalFont,buttonFont,pressFont;///****///

    goalfont.loadFromFile("data/font/Goals.ttf");
    gameoverfont.loadFromFile("data/font/gameover.ttf");
    playerfont.loadFromFile("data/font/Player.ttf");
    keyFont.loadFromFile("data/font/Player.ttf");///****///
    menuGoalFont.loadFromFile("data/font/Player.ttf");
    buttonFont.loadFromFile("data/font/Button.ttf");
    pressFont.loadFromFile("data/font/Player.ttf");

    buttonTxt.setFont(buttonFont);
    buttonTxt.setCharacterSize(80);
    buttonTxt.setFillColor(Color::Red);

    pressTxt.setFont(pressFont);
    pressTxt.setStyle(Text::Bold);
    pressTxt.setCharacterSize(80);
    pressTxt.setFillColor(Color::Red);
    pressTxt.setScale(Vector2f(.40,.40));
    //pressTxt.setString("PRESS : ");

    goalTxt.setFont(playerfont);    /**////1.1
    goalTxt.setString("GOALS ");
    //goalTxt.setStyle(sf::Text::Italic);
    goalTxt.setStyle(Text::Bold | Text::Italic);
    goalTxt.setCharacterSize(80);
    goalTxt.setScale(Vector2f(.30,.30));
    goalTxt.setPosition(0.f,60.f);
    goalTxt.setFillColor(Color::Blue);

    keyText.setFont(keyFont);      ///****///
    keyText.setCharacterSize(80);
    keyText.setScale(0.50f,.50f);
    keyText.setPosition(59,85);
    keyText.setFillColor(Color::Red);
    keyText.setString("1");

    menuGoalText.setFont(keyFont);      ///****///
    menuGoalText.setCharacterSize(80);
    menuGoalText.setScale(0.50f,.50f);
    menuGoalText.setPosition(59,133);
    menuGoalText.setFillColor(Color::Red);
    menuGoalText.setString("1");


    playerLifeTxt.setFont(playerfont);  /**////1.2
    playerLifeTxt.setCharacterSize(80);
    playerLifeTxt.setScale(0.75f,0.75f);
    playerLifeTxt.setPosition(56,181);
    playerLifeTxt.setFillColor(Color::Blue);
    playerLifeTxt.setStyle(Text::Bold);

    playerPowerTxt.setFont(playerfont); /**////1.3
    playerPowerTxt.setCharacterSize(80);
    playerPowerTxt.setScale(0.60f,0.60f);
    playerPowerTxt.setPosition(59,248);
    playerPowerTxt.setFillColor(Color::Red);
    playerPowerTxt.setStyle(Text::Bold);

    int playerLife = 2,playerPower = 2; /**////1.4
    string playerLifeString = "2";
    string playerPowerString = "2";


    ///TEXTURE DECLERATION
    sf::Texture texturePlayer;
    sf::Texture textureFrame;
    sf::Texture textureGrass;
    sf::Texture texture_death_scythe;
    sf::Texture texture_devil;
    sf::Texture texture_hulk;
    sf::Texture texture_redskull;
    sf::Texture textureBlock;
    sf::Texture Block_footbe;
    sf::Texture Block_footbe1;
    sf::Texture textureBomb;
    sf::Texture textureExplosion;
    sf::Texture textureHealth;
    sf:;Texture textureKey;
    sf::Texture texturePower;
        Texture player_sole_box;
        Texture player_sole_left_box;
        Texture player_sole_right_box;
        Texture devil_sole_box;
        Texture hulk_sole_box;
        Texture redskull_sole_box;
        Texture death_scythe_sole_box;
    sf::Texture textureGameover;
    sf::Texture textureRight;
    sf::Texture textureLeft;
    sf::Texture textureKeyAnimation;
    sf::Texture textureDoorCls;
    sf::Texture textureDoorOpn;
    sf::Texture explsole;
    sf::Texture menuGoal;
        Texture heart;
        Texture credit_tex;
        Texture instruction_text;/***////

    ///LOAD FILE
    texturePlayer.loadFromFile("data/image/kavi.png");
    textureFrame.loadFromFile("data/image/frame1.png");
    textureGrass.loadFromFile("data/image/grass.png");
    texture_death_scythe.loadFromFile("data/image/death_scythe.png");
    texture_devil.loadFromFile("data/image/devil.png");
    texture_hulk.loadFromFile("data/image/hulk.png");
    texture_redskull.loadFromFile("data/image/redskull.png");
    Block_footbe.loadFromFile("data/step0001.png");
    Block_footbe1.loadFromFile("data/image/footbe_type2.png");
    textureBlock.loadFromFile("data/image/block_fix.png");
    textureBomb.loadFromFile("data/000.png");
    textureExplosion.loadFromFile("data/explosion/boxAgun.png");
    textureHealth.loadFromFile("data/heart.png");
    textureKey.loadFromFile("data/key.png");
    texturePower.loadFromFile("data/Bolt.png");
    player_sole_box.loadFromFile("data/image/transparent.png");
    player_sole_left_box.loadFromFile("data/image/transparent.png");
    player_sole_right_box.loadFromFile("data/image/transparent.png");
    devil_sole_box.loadFromFile("data/image/transparent.png");
    hulk_sole_box.loadFromFile("data/image/transparent.png");
    redskull_sole_box.loadFromFile("data/image/transparent.png");
    death_scythe_sole_box.loadFromFile("data/image/transparent.png");
    textureGameover.loadFromFile("data/gameover.png");
    textureLeft.loadFromFile("data/arrowLeft.png");
    textureRight.loadFromFile("data/arrowRight.png");
    textureKeyAnimation.loadFromFile("data/keyAnime.png");
    textureDoorCls.loadFromFile("data/image/DoorClosed.png");
    textureDoorOpn.loadFromFile("data/image/DoorOpen.png");
    explsole.loadFromFile("data/image/transparent.png");
    menuGoal.loadFromFile("data/image/DoorOpen.png");
    heart.loadFromFile("data/image/heart_fahim.png");/****////
    credit_tex.loadFromFile("data/image/credit.png");
    instruction_text.loadFromFile("data/image/instruction1.png");
    heart.setSmooth(true);
    ///sprite decl
    sf::Sprite playerImage(texturePlayer); //,sf::IntRect(0,0,35,50)
    sf::Sprite blocki(textureBlock);
    sf::Sprite death_scythe(texture_death_scythe);
        Sprite devil(texture_devil);
        Sprite hulk(texture_hulk);
        Sprite redskull(texture_redskull);
    sf::Sprite frame(textureFrame);
    sf::Sprite grass(textureGrass);
    sf::Sprite block_foot (Block_footbe);
    sf::Sprite block_foot1 (Block_footbe1);
    sf::Sprite spriteHealth(textureHealth);
    sf::Sprite menuKey(textureKey);
    sf::Sprite spritePower(texturePower);
        Sprite player_sole(player_sole_box);
        Sprite player_sole_right(player_sole_right_box);
        Sprite player_sole_left(player_sole_left_box);
        Sprite devil_sole(devil_sole_box);
        Sprite hulk_sole(hulk_sole_box);
        Sprite redskull_sole(redskull_sole_box);
        Sprite death_scythe_sole(death_scythe_sole_box);
    sf::Sprite spriteGameover(textureGameover);
    sf::Sprite spriteLeft(textureLeft);
    sf::Sprite spriteRight(textureRight);
    sf::Sprite spriteKeyAnimation(textureKeyAnimation);
    sf::Sprite spriteDoorCls(textureDoorCls);
    sf::Sprite spriteDoorOpn(textureDoorOpn);
    sf::Sprite spriteexplsole[5];
        Sprite spriteGoal(menuGoal);
        Sprite hea[5][10];
        Sprite credit(credit_tex);
        //Sprite spriteBomb(textuteBomb);
        //Sprite spriteExplosion(textureExplosion);
        textureKeyAnimation.setSmooth(true);
        Sprite instr(instruction_text);
    ///Position
    playerImage.setPosition(186,50);
    death_scythe.setPosition(356,50);
    devil.setPosition(476,450);
    hulk.setPosition(706 ,100);
    redskull.setPosition(820,345);
    frame.setPosition(0,0);
    grass.setPosition(125,0);
    menuKey.setPosition(0,90);
    spriteHealth.setPosition(0,205);
    spritePower.setPosition(-5,250);
    spriteRight.setPosition(578.125,347.5);
    spriteLeft.setPosition(237.5,350);
    spriteKeyAnimation.setPosition(705,100);
    spriteDoorCls.setPosition(812,300);
    spriteDoorOpn.setPosition(812,300);
    sf::Sprite spriteexplsoleR[5];
    sf::Sprite spriteexplsoleL[5];
    sf::Sprite spriteexplsoleU[5];
    sf::Sprite spriteexplsoleD[5];
    spriteGoal.setPosition(5,145);
    //spriteKeyAnimation.setColor(Color(228,255,200,255));

      ///position detector
    int player_pos_x = 186,player_pos_y = 50;
    int devil_pos_x=476,devil_pos_y=450;


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
    playerImage.setScale(Vector2f(1.3f,1.2f));
    spriteLeft.setScale(0.1625f,0.1625f);
    spriteRight.setScale(0.1625f,0.1625f);
    spriteKeyAnimation.setScale(0.0802139f,0.058343f);
    spriteDoorCls.setScale(0.94f,1.2);
    spriteDoorCls.setScale(0.94f,1.2);

    devil.setScale(1.25f,1.25f);
    redskull.setScale(1.0f,.8f);
    spriteGoal.setScale(0.61403f,0.6f);
    credit.setScale(0.7f,0.78125f);
    instr.setScale(0.70826f,0.8583f);
    /***///
        ///player soles
    player_sole.setScale(Vector2f(0.000001f,.061f));
   // player_sole.setColor(Color(0, 255, 0, 0));
    player_sole_left.setScale(Vector2f(0.085f,.00001f));
    player_sole_right.setScale(Vector2f(0.03f,.061f));

    ///enemy ani
    int death_scythe_x = 0,death_scythe_y = 0;
    int devil_x = 0,devil_y = 0;
    int hulk_x = 0,hulk_y = 0;
    int redskull_x = 1,redskull_y = 1;

    int death_scythe_counter = 0;
    int devil_counter = 0;
    int hulk_counter = 0;
    int redskull_counter = 0;
    int gameoverNum = 0;

    ///devil sole
    devil_sole.setScale(Vector2f(0.04f,.019f));
    devil_sole.setColor(Color(0, 255, 0, 0));
    ///hulk sole
    hulk_sole.setScale(Vector2f(0.04f,.019f));
    hulk_sole.setColor(Color(0, 255, 0, 0));
    ///death_scythe sole
    death_scythe_sole.setScale(Vector2f(0.04f,.019f));
    death_scythe_sole.setColor(Color(0, 255, 0, 0));
    ///redskull sole
    redskull_sole.setScale(Vector2f(0.04f,.019f));
    redskull_sole.setColor(Color(0, 255, 0, 0));

    ///dataset_array
    int arr1[49]={2,5,8,11   ,1,1,3,3,3,4,4,6,7,7,7,9,9,10,10,12,12,12,2,2,2,3,4,4,5,5,5,5,6,6,7,7,8,9,10,10,11,11,12};
    int arr2[49]={2,4,6,8,10 ,5,8,1,4,6,3,9,5,3,5,9,3,6, 4, 6, 1, 5, 10,5,7,3,3,7,8,1,3,5,9,3,4,7,8,3,2, 9,10, 3, 9 ,4 ,5687687,56797980};
    for(int n=0;n<45;n++)
    {
        vect1.push_back(make_pair(arr1[n],arr2[n]));
    }
    for(int n=0;n<45;n++)
    {
        vect2.push_back(make_pair(arr1[n],arr2[n]));
    }
    for(int j=4;j<vect1.size();j++)
    {
        int xf=vect1[j].first*57+126;
        block_blast_pos_x.push_back(xf);

        int yf= vect1[j+1].second*50-5;
        block_blast_pos_y.push_back(yf);
    }


    ///heart load


        while(heart_sprite_num<=3)
        {
            for(int r=0;r<10;r++)
            {
            if(heart_sprite_num==3)
            hea[heart_sprite_num][r].setPosition(heart_sprite_num*230+93,heart_sprite_num*100+68);
            else
            hea[heart_sprite_num][r].setPosition(heart_sprite_num*230+93,heart_sprite_num*100+18);
            hea[heart_sprite_num][r].setTexture(heart);
            hea[heart_sprite_num][r].scale(0.2,0.2);
            }
            heart_sprite_num++;
        }


        while(he_sprite_num<=3)
        {
        hea[he_sprite_num][i0].setTextureRect(IntRect(0,0,252,217.5));
        hea[he_sprite_num][0].setOrigin(127.5,108);
        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(276,0,492-276,217.5));
        hea[he_sprite_num][1].setOrigin(396-276,108);

        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(516,0,694.5-516,217.5));
        hea[he_sprite_num][2].setOrigin(628.5-516,108);

        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(696.5,0,836.5-696.5,217.5));
        hea[he_sprite_num][3].setOrigin(790.5-696.5,108);

        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(862,0,938-862,217.5));
        hea[he_sprite_num][4].setOrigin(902-862,108);

        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(82.5,217.5,168-82.5,239.5));
        hea[he_sprite_num][5].setOrigin(124.5-82.5,101);

        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(192,217.5,334.4-192,239.5));
        hea[he_sprite_num][6].setOrigin(238.5-192,101);

        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(333,217.5,516-333,239.5));
        hea[he_sprite_num][7].setOrigin(396-333,101);

        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(516,217.5,763.5-516,239.5));
        hea[he_sprite_num][8].setOrigin(630-516,101);

        i0++;
        hea[he_sprite_num][i0].setTextureRect(IntRect(763.5,217.5,1014-763.5,239.5));
        hea[he_sprite_num][9].setOrigin(897-763.5,101);
        he_sprite_num++;
        i0=0;
        }

        int heart_num1=0,heart_num2=0,heart_num3=0;
     ///Time
    vector <Time>explosionTime ;
    explosionTime.clear();

    ///Clock;
    sf::Clock bombClock[5];
    sf::Clock explClock[5];
    sf::Clock levelClock;
        Clock death_scythe_clock;
        Clock devil_clock;
        Clock redskull_clock;
        Clock hulk_clock;
        Clock lovesprite_draw_clock1;
        Clock lovesprite_draw_clock2;
        Clock lovesprite_draw_clock3;
        Clock playerLifeClock[4];
       // Clock death_scythe_clock;
    classBomb vecBomb[5];
    for(int i=0; i<5; i++)
        vecBomb[i].initBomb(&textureBomb,&textureExplosion);

    ///Vector
    Sprite vecExplSprite[5];
    for(int i = 0; i < 5; i++)
    {
        vecExplSprite[i].setTexture(textureExplosion);
        vecExplSprite[i].setScale(0.1689f,0.1451475f);
        spriteexplsoleR[i].setTexture(explsole);
        spriteexplsoleR[i].setColor(Color(0, 255, 0, 0));
        spriteexplsoleR[i].setScale(0.1357f,0.019f);
        spriteexplsoleL[i].setTexture(explsole);
        spriteexplsoleL[i].setColor(Color(0, 255, 0, 0));
        spriteexplsoleL[i].setScale(0.1357f,0.019f);
        spriteexplsoleU[i].setTexture(explsole);
        spriteexplsoleU[i].setColor(Color(0, 255, 0, 0));
        spriteexplsoleU[i].setScale(0.02380f,0.5357f);
        spriteexplsoleD[i].setTexture(explsole);
        spriteexplsoleD[i].setColor(Color(0, 255, 0, 0));
        spriteexplsoleD[i].setScale(0.02380f,0.5357f);

    }

    vector <int> vecExpl[5];

    sf::SoundBuffer soundBuffer;
    sf::SoundBuffer menuBuffer;
    sf::SoundBuffer buttonBuffer;
    sf::SoundBuffer gameSelectBuffer;
    sf::SoundBuffer gameOverBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::SoundBuffer levelBuffer;

    sf::Sound gameSound;
    sf::Sound menuSound;
    sf::Sound buttonSound;
    sf::Sound gameSelectSound;
    sf::Sound gameOverSound;
    sf::Sound explosionSound;
    sf::Sound levelSound;

    soundBuffer.loadFromFile("data/music/game.wav");
    menuBuffer.loadFromFile("data/music/menupiano.wav");
    buttonBuffer.loadFromFile("data/music/button1.wav");
    gameSelectBuffer.loadFromFile("data/music/gameselect.wav");
    gameOverBuffer.loadFromFile("data/music/gameoverfail.wav");
    explosionBuffer.loadFromFile("data/music/explosion.wav");
    levelBuffer.loadFromFile("data/music//levelComplete.wav");

    gameSound.setBuffer(soundBuffer);
    menuSound.setBuffer(menuBuffer);
    buttonSound.setBuffer(buttonBuffer);
    gameSelectSound.setBuffer(gameSelectBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    explosionSound.setBuffer(explosionBuffer);
    levelSound.setBuffer(levelBuffer);

    buttonSound.setVolume(100);
    gameSound.setVolume(15);
    menuSound.setVolume(25);
    gameSelectSound.setVolume(75);
    gameOverSound.setVolume(50);
    explosionSound.setVolume(75);
    levelSound.setVolume(75);

    menuSound.play();
    menuSound.setLoop(true);
    gameSound.setLoop(true);

    Menu menu(window.getSize().x,window.getSize().y);
    bool foota_sorano_explBool[4][1];
    bool menu1 = true,game = false, gameover = false, Display = false,bomb1 = false,explosion = false ,gameBack = false,bellExplosion[5],sorano_explBool[4][5],bombBool[5],explBool[5],life = false,power = false,key_colli = false,foot_explBool[4][5],foot_sorano[36];

    bool death = false;

//    bool pl_devil_colli=false,pl_hulk_colli=false,pl_redskull_colli=false,pl_death_schythe_colli=false;
//    bool pl_agun_colli=false;
    //bool pl_life_colli[4]={false};.

    for(int i=0; i<5; i++)

    {
        bombBool[i]=false;
        explBool[i]=false;
        bellExplosion[i]=false;
    }
        for(int i = 0; i < 4; i++)
    {
        for(int j =0; j < 5;j++)
        {
            sorano_explBool[i][j] = false;
            foot_explBool[i][j] = false;
        }
    }
    for(int i = 0; i < 36; i++)
    {
        foot_sorano[i] = false;
    }

    ///INITIALIZE
    //int bombNum = 0;
    bool explosion_colli[5][4] = {false};
    vector < int > fix_x;
    vector < int > fix_y;
    for(int column=1;column<=4;column++)
        {
        for(int row=1;row<=5;row++)
        {
            int x=125+vect1[column-1].first*57+2;
            int y=vect1[row-1].second*50-5;
            fix_x.push_back(x);
            fix_y.push_back(y);
        }
        }
    bool menu_credit=false,instruction=false;
    ///bool colli
    bool player_colli[4]={false};
    bool player_colli_lR[4]={false};
    bool devil_colli[4]={false};
    bool hulk_colli[4]={false};
    bool death_scythe_colli[4]={false};
    bool redskull_colli[4]={false};
     bool pl_devil_colli=false,pl_hulk_colli=false,pl_redskull_colli=false,pl_death_schythe_colli=false,p1_expl_colli = false;
    bool pl_life_colli1=false,pl_life_colli2=false,pl_life_colli3=false;
    bool pl_agun_colli=false;

    while(window.isOpen())
    {
        Event event;
        if(menu1)
        {
            if(gameBack)
            {
                ///Position
                levelCheck=0;
                playerImage.setPosition(186,50);
                death_scythe.setPosition(356,50);
                devil.setPosition(476,450);
                hulk.setPosition(706 ,100);
                redskull.setPosition(820,350);
                for(int n=0;n<45;n++)
                   {
                    vect1[n]=vect2[n];
                    }
                //spriteRight.setPosition(237.5,375);
                //spriteLeft.setPosition(337.5,375);
                //grass.setPosition(125,0);
                player_pos_x = 186,player_pos_y = 50;
                devil_pos_x =476,devil_pos_y=450;

                death_scythe_x = 0,death_scythe_y = 0;
                devil_x = 0,devil_y = 0;
                hulk_x = 0,hulk_y = 0;
                redskull_x = 1 ,redskull_y = 1;

                death_scythe_counter = 0;
                devil_counter = 0;
                hulk_counter = 0;
                redskull_counter = 0;
                playerLife = 3,playerPower = 2;
                //spriteBomb.setPosition(player_pos_x,player_pos_y);
                //spriteExplosion.setPosition(186,50);
                pl_devil_colli=false,pl_hulk_colli=false,pl_redskull_colli=false,pl_death_schythe_colli=false,p1_expl_colli = false;
                bombNum = 0;
                gameoverNum = 0;
                key_colli = false;
                 for(int i=0; i<5; i++)

                {
                    bombBool[i]=false;
                    explBool[i]=false;
                    bellExplosion[i]=false;
                }
                for(int i = 0; i < 4; i++)
                {
                for(int j =0; j < 5;j++)
                {
                    sorano_explBool[i][j] = false;
                    foot_explBool[i][j] = false;
                }
                }
                for(int i = 0; i < 36; i++)
                {
                    foot_sorano[i] = false;
                }
                //vecBomb[]={0};
                explosionTime.clear();
            }
            Event event;
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
                                //cout << "Play button" <<endl;
                                menuSound.pause();
                                gameSound.play();
                                menu1 = false;
                                game = true;
                                life = true;
                                power = true;
                                gameover = false;
                                break;
                            case 1:
                                menu1=false;
                                instruction=true;
                                break;
                            case 2:
                                menu1=false;
                                menu_credit=true;
                                break;
                            case 3:
                                window.close();
                                break;
                        }
                    }
                    break;
                }
            }

                window.clear();
                menu.draw(window);
                window.display();
        }
        if(menu_credit)
        {
            window.clear();
            window.draw(credit);
            window.display();
            if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                        menu1=true;
                        menu_credit=false;

                }
        }
        if(instruction)
        {
            window.clear();
            window.draw(instr);
            window.display();
            if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                        menu1=true;
                        instruction=false;

                }
        }
        if(game)
        {
            Display = true;
            life = true;

            if(Keyboard::isKeyPressed(Keyboard::Escape) && game == true)
            {
                menu1 = true;
                gameBack = true;
                game = false;
                life = false;
                power = false;
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
                        if(!(player_colli[0]))
                        {
                            player.y = Down;
                            playerImage.move(0,+10);
                            player_pos_y+=10;
                        }
                    }
                    if((event.key.code == sf::Keyboard::Left) )
                    {
                        if(!(player_colli_lR[1]))
                        {
                            player.y = Left;
                            playerImage.move(-10,0);
                            player_pos_x-=10;
                        }
                    }
                    if((event.key.code == sf::Keyboard::Right) )
                    {
                        if(!(player_colli_lR[2]))
                        {
                            player.y = Right;
                            playerImage.move(+10,0);
                            player_pos_x+=10;
                        }
                    }
                    if((event.key.code == sf::Keyboard::Up)  )
                    {

                        if(!(player_colli[3]))
                        {
                            player.y = Up;
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
                        life = false;
                        power  = false;
                        gameSound.pause();
                        menuSound.play();

                        //return;
                    }
                   else if(event.key.code == sf::Keyboard::Space)
                     {
                        bombBool[bombNum] = true;
                        explBool[bombNum] = true;
                        bellExplosion[bombNum] = true;
                        bombClock[bombNum].restart();
                        explClock[bombNum].restart();
                        bomb1 = true;
                        vecBomb[bombNum].setPos(player_pos_x,player_pos_y);
                        vecBomb[bombNum].setExpl(player_pos_x,player_pos_y);
                        vecExpl[bombNum].clear();

                        int p1 = player_pos_x-129,p2 = player_pos_y-50;
                        int x,y;
                        p1 = p1%57;
                        p2 = p2%50;
                        if(p1 > 33)
                        {
                            x = player_pos_x+(57 - p1-3);
                        }
                        else
                        {
                            x = player_pos_x - p1-3;
                        }
                        if(p2 > 23)
                        {
                            y = player_pos_y+(50 - p2-7);
                        }
                        else
                        {
                            y = player_pos_y - p2-7;
                        }
                        vecExpl[bombNum].push_back(x);
                        vecExpl[bombNum].push_back(y);
                        ///cout << vecExpl[bombNum][0] << "\t";
                        //vecExpl[bombNum][0] = vecExpl[bombNum][0]+50;
                        ///cout  << vecExpl[bombNum][0] << "\t" << vecExpl[bombNum][1] << endl;
                        bombNum = (bombNum+1)%5;
                     }

                        break;
               }
                player.x++;
                if(player.x*32 >= texturePlayer.getSize().x)
                {
                    player.x = 0;
                }
                //gameover = true;
            }
            if(life)
            {
                if(pl_life_colli1)
                {
                    if(playerLife < 5)
                    {
                        playerLife++;
                       playerLifeString = To_string(playerLife);
                    }
                    pl_life_colli1=false;

                    for(int r=0;r<10;r++)
                    {
                    hea[1][r].setPosition(-230,-230);
                    }
                }
                if(pl_life_colli2)
                {
                    if(playerLife < 5)
                    {
                        playerLife++;
                       playerLifeString = To_string(playerLife);
                    }
                    pl_life_colli2=false;

                    for(int r=0;r<10;r++)
                    {
                    hea[2][r].setPosition(-230,-230);
                    }
                }
                if(pl_life_colli3)
                {
                    if(playerLife < 5)
                    {
                        playerLife++;
                       playerLifeString = To_string(playerLife);
                    }
                    pl_life_colli3=false;

                    for(int r=0;r<10;r++)
                    {
                    hea[3][r].setPosition(-230,-230);
                    }
                }
                if(pl_death_schythe_colli ||pl_devil_colli||pl_hulk_colli||pl_redskull_colli||p1_expl_colli)
                {
                    if(playerLife > 0)
                    {
                        playerLife--;
                        playerLifeString = To_string(playerLife);
                    }
                    pl_death_schythe_colli=false;
                    pl_devil_colli=false;
                    pl_hulk_colli=false;
                    pl_redskull_colli=false;
                    p1_expl_colli=false;
                    if(playerLife==0)
                       {
                           gameover=true;
                           playerLife = 2;
                           playerLifeString = To_string(playerLife);
                       }
                }
                playerLifeTxt.setString(playerLifeString);
                playerPowerTxt.setString(playerPowerString);
            }

            if(Display)
            {
             ///player_move
                window.clear();
                window.draw(frame);
                window.draw(grass);
                window.draw(goalTxt);
                window.draw(keyText);
                window.draw(menuGoalText);
                window.draw(spriteGoal);
                window.draw(playerLifeTxt);
                window.draw(playerPowerTxt);
                window.draw(menuKey);
                window.draw(spritePower);
                window.draw(spriteHealth);

                ///player enemy move texture
                playerImage.setTextureRect(IntRect(player.x * 32,player.y * 48,32,48));
                death_scythe.setTextureRect(IntRect(death_scythe_x*50, death_scythe_y*48, 50, 48));
                devil.setTextureRect(IntRect(devil_x*32, devil_y*48, 32, 48));
                hulk.setTextureRect(IntRect(hulk_x*40, hulk_y*56, 40, 56));
                redskull.setTextureRect(IntRect(redskull_x*32,redskull_y*48, 32, 48));
                ///player soles position
                player_sole.setPosition(playerImage.getPosition().x+18,playerImage.getPosition().y+40);
                player_sole_left.setPosition(playerImage.getPosition().x+5,playerImage.getPosition().y+50);
                ///devil movement
                int devil_posx=devil.getPosition().x;
                int devil_posy=devil.getPosition().y;
                devil_sole.setPosition(devil_posx,devil_posy+48);
                ///hulk movement
                int hulk_posx=hulk.getPosition().x;
                int hulk_posy=hulk.getPosition().y;
                hulk_sole.setPosition(hulk_posx,hulk_posy+48);

                ///redskull movement
                int redskull_posx=redskull.getPosition().x;
                int redskull_posy=redskull.getPosition().y;
                redskull_sole.setPosition(redskull_posx,redskull_posy+28);

                ///death_scythe movement
                int death_scythe_posx=death_scythe.getPosition().x;
                int death_scythe_posy=death_scythe.getPosition().y;
                death_scythe_sole.setPosition(death_scythe_posx,death_scythe_posy+48);
                ///ENEMY Move in spritesheet

                if(death_scythe_counter == 60)
                {
                    death_scythe_x = (death_scythe_x + 1) % 4;
                    death_scythe_counter = 0;
                }
                death_scythe_counter++;

                if(devil_counter == 60)
                {
                    devil_x = (devil_x + 1) % 4;
                    devil_counter = 0;
                }
                devil_counter++;

                if(hulk_counter == 60)
                {
                    hulk_x = (hulk_x + 1) % 4;
                    hulk_counter = 0;
                }
                hulk_counter++;

                if(redskull_counter == 60)
                {
                    redskull_x = (redskull_x + 1) % 4;
                    redskull_counter = 1;
                }
                redskull_counter++;
               ///coolision false

                for(int a=0;a<=3;a++)
                    player_colli[a]=false;
                 for(int a=0;a<=3;a++)
                    player_colli_lR[a]=false;
                for(int a=0;a<=3;a++)
                    devil_colli[a]=false;
                for(int a=0;a<=3;a++)
                    hulk_colli[a]=false;
                for(int a=0;a<=3;a++)
                    redskull_colli[a]=false;
                for(int a=0;a<=3;a++)
                    death_scythe_colli[a]=false;
                 pl_death_schythe_colli=false;
                for(int a=0;a<5;a++)
                {
                    for(int b=0;b<=3;b++)
                    {
                       explosion_colli[a][b] = false;
                    }
                }
                ///key draw
                window.draw(spriteKeyAnimation);
                for(int i = 0; i < 3; i++)
                {
                    for(int j =0; j < 1;j++)
                    {
                       foota_sorano_explBool[i][j] = false;
                    }
                }

                for(int i = 0; i < 4; i++)
                {
                    for(int j =0; j < 5;j++)
                    {
                        sorano_explBool[i][j] = false;
                        foot_explBool[i][j] = false;
                    }
                }
                for(int i = 0; i < 5; i++)              ///********///
                {
                    bool f0[5] = {false},f1[5] = {false},f2[] = {false},f3[] = {false};
                    if(explBool[i] == true)
                    {
                        int pos_X[5];
                        int pos_Y[5];
                        ///R
                        for(int j = 0; j < playerPower-1; j++)
                        {
                            pos_X[j] = vecExpl[i][0] + (j+1)*57;
                            pos_Y[0] = vecExpl[i][1]+50;

                            if(explClock[i].getElapsedTime().asSeconds() >= 6)
                            {
                                //cout << "D RRR Out\n";
                                spriteexplsoleR[j].setPosition(-450,-450);
                                window.draw(spriteexplsoleR[j]);
                                f0[j] = false;
                            }

                            if(explClock[i].getElapsedTime().asSeconds() >= 5 && explClock[i].getElapsedTime().asSeconds() < 5.8)
                            {
                                //cout << "D RRR IN\n";
                                spriteexplsoleR[j].setPosition(pos_X[j]-14.25,pos_Y[0]-12.5);
                                window.draw(spriteexplsoleR[j]);
                                f0[j]  = true;

                            }



                        }


                        ///L
                        for(int j =0; j < playerPower-1; j++)
                        {
                            pos_X[j] = vecExpl[i][0] - (j+1)*57+57;
                            pos_Y[0] = vecExpl[i][1]+50;
                            if(explClock[i].getElapsedTime().asSeconds() >= 6)
                            {
                                //cout << "D LLL OUT\n";
                                spriteexplsoleL[j].setPosition(-450,-450);
                                window.draw(spriteexplsoleL[j]);
                                f1[j] = false;
                            }
                            if(explClock[i].getElapsedTime().asSeconds() >= 5 && explClock[i].getElapsedTime().asSeconds() < 5.8)
                            {
                                //cout << "D LLL IN\n";
                                spriteexplsoleL[j].setPosition(pos_X[j]-14.25,pos_Y[0]-12.5);
                                window.draw(spriteexplsoleL[j]);
                                f1[j]  = true;
                            }
                        }
                         ///U
                        for(int j = 0; j < playerPower-1; j++)
                        {
                            pos_X[0] = vecExpl[i][0]+5;
                            pos_Y[j] = vecExpl[i][1] - (j+1)*50;

                            if(explClock[i].getElapsedTime().asSeconds() >= 6)
                            {
                                //cout << "D UUU OUT\n";
                                spriteexplsoleU[j].setPosition(-450,-450);
                                window.draw(spriteexplsoleU[j]);
                                f2[j] = false;
                            }

                            if(explClock[i].getElapsedTime().asSeconds() >= 5 && explClock[i].getElapsedTime().asSeconds() < 5.8)
                            {
                                //cout << "D UUU IN\n";
                               spriteexplsoleU[j].setPosition(pos_X[0],pos_Y[j]-20);///14.25,12.5
                               window.draw(spriteexplsoleU[j]);
                               f2[j]  = true;

                            }

                        }
                        ///D
                        for(int j = 0; j < playerPower-1; j++)
                        {
                            pos_X[0] = vecExpl[i][0]+5;
                            pos_Y[j] = vecExpl[i][1] + (j+1)*50;
                            if(explClock[i].getElapsedTime().asSeconds() >= 6)
                            {
                                //cout << "D Down OUT\n";
                                spriteexplsoleD[j].setPosition(-450,-450);
                                window.draw(spriteexplsoleD[j]);
                                f3[j] = false;
                            }

                            if(explClock[i].getElapsedTime().asSeconds() >= 5 && explClock[i].getElapsedTime().asSeconds() < 5.8)
                            {
                                //cout << "D Down IN\n";
                                spriteexplsoleD[j].setPosition(pos_X[0],pos_Y[j]-50);
                                window.draw(spriteexplsoleD[j]);
                                f3[j]  = true;

                            }
                        }
                    }
                    if(explClock[i].getElapsedTime().asSeconds() > 6)
                    {
                        for(int h = 0 ; h < playerPower-1; h++)
                        {
                            if(f0[h] == true)
                            {
                                //cout << "New RRR Out\n";
                                spriteexplsoleR[h].setPosition(-450,-450);
                                window.draw(spriteexplsoleR[h]);
                            }
                            if(f1[h] == true)
                            {
                                //cout << "New LLL OUT\n";
                                spriteexplsoleL[h].setPosition(-450,-450);
                                window.draw(spriteexplsoleL[h]);
                            }
                            if(f2[h] == true)
                            {
                                //cout << "New UUU OUT\n";
                                spriteexplsoleU[h].setPosition(-450,-450);
                                window.draw(spriteexplsoleU[h]);
                            }
                            if(f3[h] == true)
                            {
                                //cout << "New Down OUT\n";
                                spriteexplsoleD[h].setPosition(-450,-450);
                                window.draw(spriteexplsoleD[h]);
                            }
                        }
                    }
                }
                ///fix block
                for(int column=1;column<=4;column++)
                {
                    for(int row=1;row<=5;row++)
                    {

                        int x=125+vect1[column-1].first*57+2;
                        int y=vect1[row-1].second*50-5;

                        blocki.setPosition(x,y);
                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli[player.y]=true;
                           }
                        if(player_sole_left.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }
                        for(int a=0;a<5;a++)
                        {
                            if(vecExplSprite[a].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                explosion_colli[a][explosionVec.y]=true;
                            }
                        }
                        ///R
                        for(int j = 0; j < playerPower; j++)
                        {
                            if(spriteexplsoleR[j].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                sorano_explBool[0][j] = true;
                            }
                        }
                        ///L
                        for(int j =0; j < playerPower; j++)
                        {
                            if(spriteexplsoleL[j].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                sorano_explBool[1][j] = true;
                            }
                        }
                        ///U
                        for(int j =0; j < playerPower; j++)
                        {
                            if(spriteexplsoleU[j].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                sorano_explBool[2][j] = true;
                            }
                        }
                        ///D
                        for(int j =0; j < playerPower; j++)
                        {
                            if(spriteexplsoleD[j].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                sorano_explBool[3][j] = true;
                            }
                        }


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

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli[player.y]=true;
                           }
                        if(player_sole_left.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }
                        for(int a=0;a<5;a++)
                        {
                            if(vecExplSprite[a].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                    explosion_colli[a][explosionVec.y]=true;
                            }
                        }
                        ///U
                        for(int j =0; j < playerPower; j++)
                        {
                            if(spriteexplsoleU[j].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                sorano_explBool[2][j] = true;
                            }
                        }
                }
               ///lower boundery
               int dbx=67;
               for(int i=0;i<=14;i++)
                    {
                        dbx=dbx+57;
                        int y=545;
                        blocki.setPosition(dbx,y);

                        window.draw(blocki);

                         if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli[player.y]=true;
                           }
                        if(player_sole_left.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }
                       ///D
                        for(int j =0; j < playerPower; j++)
                        {
                            if(spriteexplsoleD[j].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                sorano_explBool[3][j] = true;
                            }
                        }

                        for(int a=0;a<5;a++)
                        {
                            if(vecExplSprite[a].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                explosion_colli[a][explosionVec.y]=true;
                            }
                        }

                    }

                ///left boundery
               int lby=0;
               for(int i=0;i<=11;i++)
                    {
                        int lbx=125;
                        lby+=50;
                        blocki.setPosition(lbx,lby);

                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli[player.y]=true;
                           }
                        if(player_sole_left.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }
                        for(int a=0;a<5;a++)
                        {
                            if(vecExplSprite[a].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                explosion_colli[a][explosionVec.y]=true;
                            }
                        }
                        ///L
                        for(int j =0; j < playerPower; j++)
                        {
                            if(spriteexplsoleL[j].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                sorano_explBool[1][j] = true;
                            }
                        }


                    }
                    ///last left
                        blocki.setPosition(125,545);

                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli[player.y]=true;
                           }
                        if(player_sole_left.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }
                        for(int a=0;a<5;a++)
                        {
                            if(vecExplSprite[a].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                explosion_colli[a][explosionVec.y]=true;
                            }
                        }



                ///right boundery
               int rby=0;
               for(int i=0;i<=11;i++)
                    {
                        int rbx=925-57;
                        rby+=50;
                        blocki.setPosition(rbx,rby);

                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli[player.y]=true;
                           }
                        if(player_sole_left.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }
                         ///R
                        for(int j = 0; j < playerPower; j++)
                        {
                            if(spriteexplsoleR[j].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                sorano_explBool[0][j] = true;
                            }
                        }
                        for(int a=0;a<5;a++)
                        {
                            if(vecExplSprite[a].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                explosion_colli[a][explosionVec.y]=true;
                            }
                        }

                    }
                    ///last right
                        blocki.setPosition(925-57,545);

                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli[player.y]=true;
                           }
                        if(player_sole_left.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }
                        for(int a=0;a<5;a++)
                        {
                            if(vecExplSprite[a].getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                explosion_colli[a][explosionVec.y]=true;
                            }
                        }


                ///foota block
                int j=4;
                while(j<=vect1.size())
                {
                    int playerPower=2;
                    int xf=vect1[j].first*57+126;
                    int yf= vect1[j+1].second*50-5;
                    block_foot.setPosition(xf,yf);
                    block_foot1.setPosition(xf,yf);
                    if(j<21)
                    {
                        int fanda = 0;

                        ///R
                        for(int h = 0; h < playerPower; h++)
                        {
                            if(spriteexplsoleR[h].getGlobalBounds().intersects(block_foot.getGlobalBounds()) )
                            {
                                vect1[j].first=-200;
                                vect1[j+1].second=-300;
                                foot_explBool[0][h] = true;
                                fanda = 1;
                            }
                        }
                        ///L
                        for(int h =0; h < playerPower; h++)
                        {
                            if(spriteexplsoleL[h].getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                            {
                                vect1[j].first=-2000;
                                vect1[j+1].second=-3000;
                                foot_explBool[1][h] = true;
                                fanda = 1;
                            }
                        }
                        ///U
                        for(int h =0; h < playerPower-1; h++)
                        {
                            if(spriteexplsoleU[h].getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                            {
                                vect1[j].first=-2000;
                                vect1[j+1].second=-3000;
                                foot_explBool[2][h] = true;
                                fanda = 1;
                            }
                        }
                        ///D
                        for(int h =0; h < playerPower-1; h++)
                        {
                            if(spriteexplsoleD[h].getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                            {
                                vect1[j].first=-2000;
                                vect1[j+1].second=-3000;
                                foot_explBool[3][h] = true;
                                fanda = 1;
                            }
                        }
                        if(fanda==1)
                        {
                            for(int h = 0; h < 5; h++)
                            {
                                if(explBool[h] == true)
                                {
                                    if(explClock[h].getElapsedTime().asSeconds() >= 5.2)
                                    {
                                        cout << "Left" << endl;
                                        block_foot.setPosition(-400,-400);
                                        window.draw(block_foot);
                                    }
                                }
                            }

                        }
                        else
                        {
                            window.draw(block_foot);
                        }


                        if(player_sole.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                        {
                                player_colli[player.y]=true;
                        }
                        if(player_sole_left.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }


                    }
                    else
                    {
                        int fanda = 0;

                        ///R
                        for(int h = 0; h < playerPower; h++)
                        {
                             if(sorano_explBool[0][h] == true)
                            {
                                       // cout << "CACACACACACCACACACA" << endl;
                                        break;
                            }
                            if(spriteexplsoleR[h].getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                            {
                                vect1[j].first=-2000;
                                vect1[j+1].second=-3000;
                                foot_explBool[0][h] = true;
                                fanda = 1;
                            }
                        }
                        ///L
                        for(int h =0; h < playerPower; h++)
                        {
                            if(sorano_explBool[1][h] == true)
                            {
                                       // cout << "CACACACACACCACACACA" << endl;
                                        break;
                            }
                            if(spriteexplsoleL[h].getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                            {
                                vect1[j].first=-2000;
                                vect1[j+1].second=-3000;
                                foot_explBool[1][h] = true;
                                fanda = 1;
                            }
                        }
                        ///U++
                        for(int h =0; h < playerPower-1; h++)
                        {
                            if(sorano_explBool[2][h] == true)
                            {
                                       // cout << "CACACACACACCACACACA" << endl;
                                        break;
                            }
                            if(spriteexplsoleU[h].getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                            {
                                vect1[j].first=-2000;
                                vect1[j+1].second=-3000;
                                foot_explBool[2][h] = true;
                                fanda = 1;
                            }
                        }
                        ///D
                        for(int h =0; h < playerPower-1; h++)
                        {
                            if(sorano_explBool[3][h] == true)
                            {
                                       // cout << "CACACACACACCACACACA" << endl;
                                        break;
                            }
                            if(spriteexplsoleD[h].getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                            {
                                vect1[j].first=-2000;
                                vect1[j+1].second=-3000;
                                foot_explBool[3][h] = true;
                                fanda = 1;
                            }
                        }
                        if(fanda==1)
                        {
                            //cout << "Left" << endl;
                            //block_foot1.setPosition(-200,-200);
                            //window.draw(block_foot1);
                        }
                        else
                        {
                            window.draw(block_foot1);
                        }

                        if(player_sole.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                        {
                                player_colli[player.y]=true;
                        }
                        if(player_sole_left.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                           {
                                player_colli_lR[player.y]=true;
                           }
                        if(hulk_sole.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                           {
                                hulk_colli[hulk_dir.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                           {
                                devil_colli[devil_dir.y]=true;
                           }
                        if(death_scythe_sole.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                           {
                                death_scythe_colli[death_scythe_dir.y]=true;
                           }
                        if(redskull_sole.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                           {
                                redskull_colli[redskull_dir.y]=true;
                           }
                    }
                    j++;
                }



                if(playerImage.getGlobalBounds().intersects(spriteKeyAnimation.getGlobalBounds()))
                {
                    key_colli = true;

                }
                if(key_colli)
                {
                    spriteDoorCls.setPosition(-250,-250);
                    spriteKeyAnimation.setPosition(-250,-250);
                    window.draw(spriteDoorOpn);
                }
                if(playerImage.getGlobalBounds().intersects(spriteDoorOpn.getGlobalBounds()) && levelCheck != 1)
                {
                    gameSound.pause();
                    levelSound.play();
                    levelClock.restart();
                    levelCheck = 1;
                }

                  if(levelClock.getElapsedTime().asSeconds() > 2 && levelCheck == 1)
                {
                        menu1 = true;
                        gameBack = true;
                        game = false;
                        gameover = false;
                        Display = false;
                        gameSound.pause();
                        menuSound.play();
                        //levelCheck = 0;
                }
                window.draw(spriteDoorCls);
                //window.draw(_box);
                ///FOR DEVIL KILL

                ///R
                for(int h =0; h < playerPower; h++)
                {
                    if(Collision::PixelPerfectTest(spriteexplsoleR[h],devil))
                    {
                        devil.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleR[h],hulk))
                    {
                        hulk.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleR[h],redskull))
                    {
                        redskull.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleR[h],death_scythe))
                    {
                        death_scythe.setPosition(-300,-300);
                    }

                }
                 ///L
                for(int h =0; h < playerPower; h++)
                {
                    if(Collision::PixelPerfectTest(spriteexplsoleL[h],devil))
                    {
                        devil.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleL[h],hulk))
                    {
                        hulk.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleL[h],redskull))
                    {
                        redskull.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleL[h],death_scythe))
                    {
                        death_scythe.setPosition(-300,-300);
                    }

                }
                ///U
                for(int h =0; h < playerPower; h++)
                {
                    if(Collision::PixelPerfectTest(spriteexplsoleU[h],devil))
                    {
                        devil.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleU[h],hulk))
                    {
                        hulk.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleU[h],redskull))
                    {
                        redskull.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleU[h],death_scythe))
                    {
                        death_scythe.setPosition(-300,-300);
                    }

                }
                ///D
                for(int h =0; h < playerPower; h++)
                {
                    if(Collision::PixelPerfectTest(spriteexplsoleD[h],devil))
                    {
                        devil.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleD[h],hulk))
                    {
                        hulk.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleD[h],redskull))
                    {
                        redskull.setPosition(-300,-300);
                    }
                    if(Collision::PixelPerfectTest(spriteexplsoleD[h],death_scythe))
                    {
                        death_scythe.setPosition(-300,-300);
                    }

                }
                /// Player  Explosion


                for(int h =0; h < playerPower; h++)
                {
                    ///R
                      if(Collision::PixelPerfectTest(spriteexplsoleR[h],playerImage) && p1_expl_colli == false && l0 ==false)
                    {
                        if(playerLifeClock[0].getElapsedTime().asSeconds() > 2 )
                        {
                            //cout << "RRRRRR\n";
                            l0 = true;
                            playerLifeClock[0].restart();
                            p1_expl_colli = true;
                        }
                    }
                    ///L
                    else if(Collision::PixelPerfectTest(spriteexplsoleL[h],playerImage) && p1_expl_colli == false && l1 == false)
                    {
                        if(playerLifeClock[1].getElapsedTime().asSeconds() > 2)
                        {
                            //cout << "LLLLLL\n";
                            l1 = true;
                            playerLifeClock[1].restart();
                            p1_expl_colli = true;
                        }
                    }

                    ///U
                     else if(Collision::PixelPerfectTest(spriteexplsoleU[h],playerImage) && p1_expl_colli == false && l2 == false)
                    {
                        if(playerLifeClock[2].getElapsedTime().asSeconds() > 2)
                        {
                            //cout << "UUUUUU\n";
                            l2 = true;
                            playerLifeClock[2].restart();
                            p1_expl_colli = true;
                        }
                    }

                ///D
                    else if(Collision::PixelPerfectTest(spriteexplsoleD[h],playerImage) && p1_expl_colli == false && l3 == false)
                    {
                        if(playerLifeClock[3].getElapsedTime().asSeconds() > 2)
                        {
                            //cout << "DDDDDD\n";
                            l3 = true;
                            playerLifeClock[3].restart();
                            p1_expl_colli = true;
                        }
                    }
                    else
                    {
                        p1_expl_colli = false;
                    }
                }
                                ///for devil

                if(devil_colli[0])
                {

                        devil_y=3;
                        devil_dir.y=Up;
                        devil.move(0,-1.5);
                        devil_sole.move(0,-1.5);

                        devil_dir_y=-devil_dir_y;
                }
                 else if(devil_colli[3])
                {

                        devil_y=0;
                        devil.move(0,.15);

                        devil_dir.y=Down;
                        devil_dir_y=-devil_dir_y;
                }

                devil.move(devil_dir_x,devil_dir_y);
                window.draw(devil_sole);

                 ///for hulk

                if(hulk_colli[0])
                {

                        hulk_y=3;
                        hulk_dir.y=Up;
                        hulk.move(0,-1.5);
                        hulk_sole.move(0,-1.5);

                        hulk_dir_y=-hulk_dir_y;
                }
                 else if(hulk_colli[3])
                {
                        hulk_y=0;
                        hulk.move(0,.15);

                        hulk_dir.y=Down;
                        hulk_dir_y=-hulk_dir_y;
                }

                hulk.move(hulk_dir_x,hulk_dir_y);

                window.draw(hulk_sole);
                ///for redskull

                if(redskull_colli[1])
                {
                   // cout<<endl<<"redskull_collided"<<endl;
                        redskull_y=2;
                        redskull_dir.y=Right;
                        redskull.move(1.5,0);
                        redskull_sole.move(1.5,0);

                        redskull_dir_x=-redskull_dir_x;
                }
                 else if(redskull_colli[2])
                {

                        redskull_y=1;
                        redskull.move(-1.5,0);

                        redskull_dir.y=Left;
                        redskull_dir_x=-redskull_dir_x;
                }

                redskull.move(redskull_dir_x,redskull_dir_y);
                window.draw(redskull_sole);
                ///for death_scythe

                if(death_scythe_colli[0])
                {
                   // cout<<endl<<"death_scythe_collided"<<endl;
                        death_scythe_y=3;
                        death_scythe_dir.y=Up;
                        death_scythe.move(0,-1.5);
                        death_scythe_sole.move(0,-1.5);

                        death_scythe_dir_y=-death_scythe_dir_y;
                }
                 else if(death_scythe_colli[3])
                {
                   //cout<<endl<<"death_scythe_collided"<<endl;
                        death_scythe_y=0;
                        death_scythe.move(0,.15);

                        death_scythe_dir.y=Down;
                        death_scythe_dir_y=-death_scythe_dir_y;
                }

                death_scythe.move(death_scythe_dir_x,death_scythe_dir_y);

                window.draw(death_scythe_sole);
                window.draw(player_sole);
                window.draw(player_sole_left);
                window.draw(playerImage);
                window.draw(death_scythe);
                window.draw(devil);
                window.draw(hulk);
                window.draw(redskull);
                if(heart_num1==9)
                    heart_num1=0;
                if(heart_num2==9)
                    heart_num2=0;
                if(heart_num3==9)
                    heart_num3=0;
                   // cout<<heart_num;
                    window.draw(hea[1][heart_num1]);
                   if(lovesprite_draw_clock1.getElapsedTime().asSeconds() >.09){
                        heart_num1++;
                        lovesprite_draw_clock1.restart();
                   }
                   window.draw(hea[2][heart_num1]);
                    if(lovesprite_draw_clock2.getElapsedTime().asSeconds() >.04){
                        heart_num2++;
                        lovesprite_draw_clock2.restart();

                   }
                   window.draw(hea[3][heart_num3]);
                   if(lovesprite_draw_clock3.getElapsedTime().asSeconds() >.08){
                        heart_num3++;
                        lovesprite_draw_clock3.restart();
                   }

                    if(Collision::PixelPerfectTest(hea[1][heart_num1],playerImage))
                    {
                       pl_life_colli1=true;
                        //cout << "PLAYER collision life" << endl;
                    }

                    if(Collision::PixelPerfectTest(hea[2][heart_num2],playerImage))
                    {
                        pl_life_colli2=true;
                        //cout << "PLAYER collision life" << endl;
                    }

                    if(Collision::PixelPerfectTest(hea[3][heart_num2],playerImage))
                    {
                        pl_life_colli3=true;
                        //cout << "PLAYER collision life" << endl;
                    }

                    if(Collision::PixelPerfectTest(death_scythe,playerImage) )
                    {
                        if(death_scythe_clock.getElapsedTime().asSeconds() > 2.5)
                        {
                            death_scythe_clock.restart();
                            pl_death_schythe_colli=true;
                        }
                    }

                if(Collision::PixelPerfectTest(devil,playerImage))
                {
                    if(devil_clock.getElapsedTime().asSeconds() > 2.5)
                        {
                            devil_clock.restart();
                            pl_devil_colli=true;
                        }
                }
                if(Collision::PixelPerfectTest(hulk,playerImage))
                {
                   if(hulk_clock.getElapsedTime().asSeconds() > 2.5)
                        {
                            hulk_clock.restart();
                            pl_hulk_colli=true;
                        }
                }
                if(Collision::PixelPerfectTest(redskull,playerImage))
                {
                    if(redskull_clock.getElapsedTime().asSeconds() > 2.5)
                        {
                            redskull_clock.restart();
                            pl_redskull_colli=true;
                        }
                }
                if(bomb1)
                {
                    //bomb.Draw(window,player_pos_x,player_pos_y);
                    ///explosionTime = explosionClock.getElapsedTime();
                    ///window.draw(spriteBomb);
                    for(int i = 0; i < 5; i++)
                    {
                        window.draw(vecBomb[i].spriteBomb);
                        explosion = true;
                       // bellExplosion = true;
                        if(explBool[i] == true)
                        {
                            //cout <<  vecExpl[i][0] << "\t" << vecExpl[i][1] << endl;
                            if(explClock[i].getElapsedTime().asSeconds() >= 6)
                            {
                                vecBomb[i].setExpl(-150,-150);
                                explBool[i] = false;
                            }
                            if(explClock[i].getElapsedTime().asSeconds() >= 5)
                            {
                                //cout << "EXPLOSION";
                                if(bellExplosion[i] == true)
                                {
                                    explosionSound.play();
                                    bellExplosion[i] = false;
                                }

                                //gameSound.pause();
                                window.draw(vecBomb[i].spriteExplosion);
                                int pos_X[5];
                                int pos_Y[5];
                                ///RIGHT
                                for(int j = 0; j < playerPower; j++)
                                {
                                    pos_X[j] = vecExpl[i][0] + (j+1)*57;
                                    pos_Y[0] = vecExpl[i][1];
                                    vecExplSprite[j].setPosition(pos_X[j]-14.25,pos_Y[0]-12.5);
                                    //spriteexplsole[j].setPosition(pos_X[j]-14.25,pos_Y[0]-12.5);
                                }
                                for(int j = 0; j < playerPower; j++)
                                {
                                    if(sorano_explBool[0][j] == true)
                                    {
                                       // cout << "CACACACACACCACACACA" << endl;
                                        break;
                                    }
                                    else
                                    {
                                        window.draw(vecExplSprite[j]);
                                    }

                                   // window.draw(spriteexplsole);

                                }
                                ///LEFT
                                for(int j = 0; j < playerPower; j++)
                                {
                                    pos_X[j] = vecExpl[i][0] - (j+1)*57;
                                    pos_Y[0] = vecExpl[i][1];
                                    vecExplSprite[j].setPosition(pos_X[j]-14.25,pos_Y[0]-12.5);
                                }
                                for(int j = 0; j < playerPower; j++)
                                {
                                        //window.draw(spriteexplsole);
                                    if(sorano_explBool[1][j] == true)
                                    {
                                        //cout << "Left" << endl;
                                        break;
                                    }
                                    else
                                    {
                                        window.draw(vecExplSprite[j]);
                                    }
                                }
                                ///UP
                                for(int j = 0; j < playerPower; j++)
                                {
                                    pos_X[0] = vecExpl[i][0];
                                    pos_Y[j] = vecExpl[i][1] - (j+1)*50;
                                    vecExplSprite[j].setPosition(pos_X[0]-14.25,pos_Y[j]-12.5);
                                }
                                for(int j = 0; j < playerPower; j++)
                                {
                                    if(sorano_explBool[2][j] == true)
                                    {
                                        //cout << "UP" << endl;
                                        break;
                                    }
                                    else
                                    {
                                        window.draw(vecExplSprite[j]);
                                    }
                                }
                                ///DOWN
                                int d;
                                for(int j = 0; j < playerPower; j++)
                                {
                                    pos_X[0] = vecExpl[i][0];
                                    pos_Y[j] = vecExpl[i][1] + (j+1)*50;
                                    vecExplSprite[j].setPosition(pos_X[0]-14.25,pos_Y[j]-12.5);

                                }
                                for(int j = 0; j < playerPower; j++)
                                {
                                        if(sorano_explBool[3][j] == true)
                                    {
                                        //cout << "Down" << endl;
                                        break;
                                    }
                                    else
                                    {
                                        d=j;
                                        window.draw(vecExplSprite[j]);
                                    }
                                }
                            //cout<<pos_X[0]-14.25<<" "<<pos_Y[d]-12.25;
                                /*int pos_X1 = vecExpl[i][0] + 1*57;
                                int pos_X2 = vecExpl[i][0] + 2*57;
                                int pos_X3 = vecExpl[i][0] + 3*57;
                                int pos_Y = vecExpl[i][1];*/
                                    //vecExpl[i][0] = vecExpl[i][0] + 50;
                                    //cout <<  vecExpl[i][0] << "\t" << vecExpl[i][1] << endl;
                                    /*vecExplSprite[0].setPosition(pos_X1-14.25,pos_Y-12.5);
                                    vecExplSprite[1].setPosition(pos_X2-14.25,pos_Y-12.5);
                                    vecExplSprite[2].setPosition(pos_X3-14.25,pos_Y-12.5);*/
                                    /*window.draw(vecExplSprite[0]);
                                    window.draw(vecExplSprite[1]);
                                    window.draw(vecExplSprite[2]);*/


                            }
                            //gameSound.play();

                        }
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
                if(gameover)
                {
                    window.clear();
                    gameSound.pause();
                    if(gameoverNum == 0)
                    {
                        gameOverSound.play();
                    }
                    gameoverNum++;
                    window.draw(spriteGameover);
                    pressTxt.setPosition(237.5-5,350+70);
                    pressTxt.setString("PRESS : Q");
                    window.draw(pressTxt);
                    pressTxt.setPosition(578.125-5,347.5+70);
                    pressTxt.setString("PRESS : W");
                    window.draw(pressTxt);

                    window.draw(spriteRight);
                    window.draw(spriteLeft);
                    if(Keyboard::isKeyPressed(Keyboard::Q))
                    {
                        //spriteRight.setPosition(-300,-300);
                        gameSelectSound.play();
                        gameOverSound.pause();
                        menu1 = true;
                        gameBack = true;
                        game = false;
                        gameover = false;
                        Display = false;
                        gameSound.pause();
                        menuSound.play();
                    }
                    if(Keyboard::isKeyPressed(Keyboard::W))
                    {
                        //spriteLeft.setPosition(-300,-300);
                        gameSelectSound.play();
                        gameOverSound.pause();
                        gameoverNum = 0;
                        menu1 = false;
                        gameBack = true;
                        game = true;
                        gameover = false;
                        Display = false;
                        menuSound.pause();
                        gameSound.play();

                    }
                    //gameOverSound.pause();
                }
                    window.display();
            }
        }
    }
}
