#include "enemy.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "animatedsprite.h"
#include <iostream>
#include <vector>
#include "bullet.h"

Enemy::Enemy()
{
    sf::Texture tx_enemy;
    if(!tx_enemy.loadFromFile("texture/enemy.png")){std::cout<<"dick"<<std::endl;}
    setTexture(tx_enemy);
    setTextureRect(sf::IntRect(0,00,60,60));
    setOrigin(30,30);

}

void Enemy::attack(sf::Window &w,std::vector<Enemy> &en)
{
    int ts=timespawn;    
    if(ts<timespawn)
    {
        ts++;
    }
    else if(ts>=timespawn&&en.size()<enemycounter)
    {
        setPosition(sf::Vector2f(rand()%w.getSize().x,rand()%w.getSize().y));
        //en.emplace_back(this->);

        ts=0;
    }
}

//void Enemy::setpos(float x1,float y1)
//{
    //this->setPosition(sf::Vector2f(x1,y1));
//}


void Enemy::animate(const sf::Time &elapsed,const std::vector<sf::Sprite> &walls,AnimatedSprite pl)
{
    sf::Vector2f pl_position = pl.getPosition();
    const float PI=3.14159265;
    float mx=this->getPosition().x-pl_position.x;
    float my=this->getPosition().y-pl_position.y;
    float rot=atan2(my,mx)*180/PI+180;
    this->setRotation(rot);

}



