#include "animatedsprite.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

#include "enemy.h"
#include "bullet.h"
#include <iostream>

AnimatedSprite::AnimatedSprite()
{
    life=30;
}

void AnimatedSprite::rotating(sf::RenderWindow &w)
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(w);
    const float PI=3.14159265;
    float mx=this->getPosition().x-mouse_position.x;
    float my=this->getPosition().y-mouse_position.y;
    float rot=atan2(my,mx)*180/PI+180;
    this->setRotation(rot);
}

void AnimatedSprite::animate(const sf::Time &elapsed,const std::vector<sf::Sprite> &walls)
{
    auto bounds=getGlobalBounds();
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
    {
        if(bounds.top>bounds_top_)
        {
           move(0,-velocity_y*elapsed.asSeconds());
           for (auto &r:walls)
           {
               if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
               {move(0,velocity_y*elapsed.asSeconds());}
           }
        }
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
    {
        if(bounds.top+bounds.height<bounds_bottom_)
        {
        move(0,velocity_y*elapsed.asSeconds());
        for (auto &r:walls)
        {
            if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
            {move(0,-velocity_y*elapsed.asSeconds());}
        }
        }
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
    {
        if(bounds.left>bounds_left_)
        {
        move(-velocity_x*elapsed.asSeconds(),0);
        for (auto &r:walls)
        {
            if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
            {move(velocity_x*elapsed.asSeconds(),0);}
        }
        }
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
    {
        if(bounds.left+bounds.width<bounds_right_)
        {
        move(velocity_x*elapsed.asSeconds(),0);
        for (auto &r:walls)
        {
            if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
            {move(-velocity_x*elapsed.asSeconds(),0);}
        }
        }
    }
}

void AnimatedSprite::shooting(sf::RenderWindow &w,std::vector<Bullet> &b,const std::vector<sf::Sprite> &walls,std::vector<Enemy> &en,Bullet &b1)
{
    sf::Vector2f playercenter;
    playercenter.x=this->getPosition().x;
    playercenter.y=this->getPosition().y;

    sf::Vector2f mousepos=sf::Vector2f(sf::Mouse::getPosition(w));
    sf::Vector2f aimdir=mousepos-playercenter;
    sf::Vector2f aimdirnorm;
    aimdirnorm.x=aimdir.x / sqrt(pow(aimdir.x,2)+pow(aimdir.y,2));
    aimdirnorm.y=aimdir.y / sqrt(pow(aimdir.x,2)+pow(aimdir.y,2));



    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(b1.sp>=b1.speedshoot)
        {
            b1.shoot.play();
            b1.shape_bullet.setPosition(playercenter);
            b1.velocity_bullet=aimdirnorm*b1.maxspeed;
            b.emplace_back(Bullet(b1));
            b1.sp=0;
        }
        b1.sp++;
    };

    for(size_t i=0;i<b.size();i++)
    {
        for (auto &r:walls)
        {
            if(r.getGlobalBounds().intersects(b[i].shape_bullet.getGlobalBounds()))
            {b.erase(b.begin()+i);break;}}
        b[i].shape_bullet.move(b[i].velocity_bullet);
        if(b[i].shape_bullet.getPosition().x<0||
                b[i].shape_bullet.getPosition().x>w.getSize().x||
                b[i].shape_bullet.getPosition().y<0||
                b[i].shape_bullet.getPosition().y>w.getSize().y)
        {
            b.erase(b.begin()+i);
        }
        else
        {
            for(size_t k=0;k<en.size();k++)
            {
            if(b[i].shape_bullet.getGlobalBounds().intersects(en[k].getGlobalBounds()))
            {

                en[k].life-=b1.damage;
                if(en[k].life<=0)
                {
                    point+=1;
                    en.erase(en.begin()+k);
                    b1.damage+=(b1.damage/25);
                    if(b1.maxspeed<5)
                    {
                    b1.maxspeed+=0.01;
                    }
                    if(b1.speedshoot>100)
                    {
                    b1.speedshoot-=1;
                    }
                }

                b.erase(b.begin()+i+1);
                break;
            }
            }

        }

    }



}
