#include "animatedsprite.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "enemy.h"
#include "bullet.h"

AnimatedSprite::AnimatedSprite()
{

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
