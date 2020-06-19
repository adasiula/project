#include "bullet.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <vector>

#include <enemy.h>

Bullet::Bullet(float radius)
{
    currVelocity=sf::Vector2f(0.0,0.0);
    maxspeed=3.0;
    speedshoot=50;//700;
    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::Yellow);
};

void Bullet::shooting(sf::RenderWindow &w,std::vector<Bullet> &b,sf::Vector2f p,const std::vector<sf::Sprite> &walls,std::vector<sf::Sprite> &en)
{
    Bullet b_p;
    //sf::Texture tx;
    //if(!tx.loadFromFile("texture/bullet.png")){
    //    std::cout<<"not loaded"<<std::endl;
   // }
    //b_p.setTexture(tx);

    playercenter=p;
    mousepos=sf::Vector2f(sf::Mouse::getPosition(w));
    aimdir=mousepos-playercenter;
    aimdirnorm.x=aimdir.x / sqrt(pow(aimdir.x,2)+pow(aimdir.y,2));
    aimdirnorm.y=aimdir.y / sqrt(pow(aimdir.x,2)+pow(aimdir.y,2));

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(sp<1)
        {
            b_p.shape.setPosition(playercenter);
            b_p.currVelocity=aimdirnorm*b_p.maxspeed;
            b.emplace_back(Bullet(b_p));
            sp=b_p.speedshoot;
        }
        sp--;
    };

    for(auto i=0;i<b.size();i++)
    {
        for (auto &r:walls)
        {
            if(r.getGlobalBounds().intersects(b[i].shape.getGlobalBounds()))
            {b.erase(b.begin()+i);break;}}
        b[i].shape.move(b[i].currVelocity);
        if(b[i].shape.getPosition().x<0||
                b[i].shape.getPosition().x>w.getSize().x||
                b[i].shape.getPosition().y<0||
                b[i].shape.getPosition().y>w.getSize().y)
        {
            b.erase(b.begin()+i);
        }
        else
        {
            for(auto k=0;k<en.size();k++)
            {
            if(b[i].shape.getGlobalBounds().intersects(en[k].getGlobalBounds()))
            {
                en.erase(en.begin()+k);

                b.erase(b.begin()+i+1);
                break;
            }
            }

        }

    }



};

void Bullet::settx(sf::Texture &tx)
{
    //this->setTexture(tx);
    //std::cout<<"loaded 2 "<<std::endl;

}

/*void Bullet::shooting2(sf::RenderWindow &w,std::vector<Bullet> &b,sf::Vector2f p,const std::vector<sf::Sprite> &walls,std::vector<Enemy> &en)
{
    Bullet b_p;

    playercenter=p;
    mousepos=sf::Vector2f(sf::Mouse::getPosition(w));
    aimdir=mousepos-playercenter;
    aimdirnorm.x=aimdir.x / sqrt(pow(aimdir.x,2)+pow(aimdir.y,2));
    aimdirnorm.y=aimdir.y / sqrt(pow(aimdir.x,2)+pow(aimdir.y,2));

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(sp<1)
        {
            b_p.shape.setPosition(playercenter);
            b_p.currVelocity=aimdirnorm*b_p.maxspeed;
            b.emplace_back(Bullet(b_p));
            sp=b_p.speedshoot;
        }
        sp--;
    };

    for(auto i=0;i<b.size();i++)
    {
        for (auto &r:walls)
        {
            if(r.getGlobalBounds().intersects(b[i].shape.getGlobalBounds()))
            {b.erase(b.begin()+i);break;}}
        b[i].shape.move(b[i].currVelocity);
        if(b[i].shape.getPosition().x<0||
                b[i].shape.getPosition().x>w.getSize().x||
                b[i].shape.getPosition().y<0||
                b[i].shape.getPosition().y>w.getSize().y)
        {
            b.erase(b.begin()+i);
        }
        else
        {
            for(auto k=0;k<en.size();k++)
            {
            if(b[i].shape.getGlobalBounds().intersects(en[k].getGlobalBounds()))
            {
                en.erase(en.begin()+k);

                b.erase(b.begin()+i+1);
                break;
            }
            }

        }

    }



};*/
