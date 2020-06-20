#include "bullet.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <vector>

#include "enemy.h"
#include "animatedsprite.h"

Bullet::Bullet(float radius)
{
    currVelocity=sf::Vector2f(0.0,0.0);
    maxspeed=start_maxspeed;
    speedshoot=start_speedshoot;//700;
    damage=startdamage;

    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::Yellow);
};

void Bullet::shooting(sf::RenderWindow &w,std::vector<Bullet> &b,sf::Vector2f p,const std::vector<sf::Sprite> &walls,std::vector<Enemy> &en)
{
    Bullet b_p;

    playercenter=p;
    mousepos=sf::Vector2f(sf::Mouse::getPosition(w));
    aimdir=mousepos-playercenter;
    aimdirnorm.x=aimdir.x / sqrt(pow(aimdir.x,2)+pow(aimdir.y,2));
    aimdirnorm.y=aimdir.y / sqrt(pow(aimdir.x,2)+pow(aimdir.y,2));

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(sp>=speedshoot)
        {
            b_p.shape.setPosition(playercenter);
            b_p.currVelocity=aimdirnorm*maxspeed;
            b.emplace_back(Bullet(b_p));
            sp=0;
        }
        sp++;
    };

    for(size_t i=0;i<b.size();i++)
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
            for(size_t k=0;k<en.size();k++)
            {
            if(b[i].shape.getGlobalBounds().intersects(en[k].getGlobalBounds()))
            {
                en[k].life-=damage;
                /*std::cout<<"damage: "<<damage
                        <<"\nmaxspeed: "<<maxspeed
                       <<"\nspeedshot: "<<speedshoot<<std::endl;*/
                std::cout<<en[k].life<<std::endl;
                if(en[k].life<=0)
                {
                    en.erase(en.begin()+k);
                    damage+=10;
                    if(maxspeed<7)
                    {
                    maxspeed+=1;
                    }
                    if(speedshoot>100)
                    {
                    speedshoot-=10;
                    }
                }

                b.erase(b.begin()+i+1);
                break;
            }
            }

        }

    }



};
