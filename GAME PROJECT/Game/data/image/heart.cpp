#include<SFML/Graphics.hpp>
using namespace sf;
#include <bits/stdc++.h>
using namespace std;
#define win_W 1280
// RenderWindow window1;
RenderWindow window1(VideoMode(win_W, 620), "Four Wheeler Racing");


class life
{
    Texture heart;
    int curr=0,j=0,n=+5;
    public:
    Sprite hea[10];
    int start_point=7;
    bool f=0;
    void init()
    {
        heart.loadFromFile("heart.png");
        heart.setSmooth(true);
        int i=0;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(0,0,252,217.5));
        hea[0].setOrigin(127.5,108);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(276,0,492-276,217.5));
        hea[1].setOrigin(396-276,108);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(516,0,694.5-516,217.5));
        hea[2].setOrigin(628.5-516,108);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(696.5,0,836.5-696.5,217.5));
        hea[3].setOrigin(790.5-696.5,108);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(862,0,938-862,217.5));
        hea[4].setOrigin(902-862,108);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(82.5,217.5,168-82.5,239.5));
        hea[5].setOrigin(124.5-82.5,101);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(192,217.5,334.4-192,239.5));
        hea[6].setOrigin(238.5-192,101);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(333,217.5,516-333,239.5));
        hea[7].setOrigin(396-333,101);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(516,217.5,763.5-516,239.5));
        hea[8].setOrigin(630-516,101);
        hea[i].scale(0.2,0.2);
        i++;
        hea[i].setPosition(start_point,500);
        hea[i].setTexture(heart);
        hea[i].setTextureRect(IntRect(763.5,217.5,1014-763.5,239.5));
        hea[9].setOrigin(897-763.5,101);
        hea[i].scale(0.2,0.2);
    }
    void move()
    {
        j++;
        if(j==n-1)curr++;
        j%=n;
        curr%=10;
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            for(int i=0;i<10;i++)hea[i].move(-10,0);
        }
        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            for(int i=0;i<10;i++)hea[i].move(10,0);
        }
        // cout<<flag<<' '<<pa.getPosition().y<<' '<<curr_v<<endl;

    }
    void draw()
    {
        window1.draw(hea[curr]);
    }
};





int main() {
    window1.setFramerateLimit(60);
    life ha;
    vector<life>ha_vec;
    ha.init();
    int ha_timer=80;
    while(window1.isOpen()) {
        Event event;
        while(window1.pollEvent(event)) {
            if(event.type == event.Closed) window1.close();
        }

        if(ha_timer>=80){
            ha_timer=0;
            ha_vec.push_back(ha);
        }else{
            ha_timer++;
        }

        window1.clear();
        for(int i=0;i<ha_vec.size();i++){
            ha_vec[i].move();
            ha_vec[i].draw();
        }

        window1.display();

    }
}
