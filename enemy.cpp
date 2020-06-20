#include "enemy.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "animatedsprite.h"
#include "bullet.h"

Enemy::Enemy()
{
    sf::Texture tx_enemy;
    if(!tx_enemy.loadFromFile("texture/enemy.png")){std::cout<<"not loaded"<<std::endl;}
    this->setTexture(tx_enemy);
    this->setTextureRect(sf::IntRect(0,0,60,60));
    this->setOrigin(30,30);
    enemycounter=6;
    timespawn=800;
    life=start_life;
    std::cout<<life<<std::endl;
}

void Enemy::attack(AnimatedSprite pl,sf::Time &elapsed,std::vector<sf::Sprite> &walls)
{
    pl_position = pl.getPosition();
    e_position=getPosition();
    if(pl_position.y>e_position.y)
    {
        if(pl_position.x>e_position.x)
        {
            move(evelocity_x*elapsed.asSeconds(),evelocity_y*elapsed.asSeconds());
            for (auto &r:walls){
                if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
                {
                    move(-abs(evelocity_x*elapsed.asSeconds()),-abs(evelocity_y*elapsed.asSeconds()));
                }
            }
        }
        else if(pl_position.x<e_position.x)
        {
            move(-abs(evelocity_x*elapsed.asSeconds()),evelocity_y*elapsed.asSeconds());
            for (auto &r:walls){
                if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
                {
                    move(abs(evelocity_x*elapsed.asSeconds()),-abs(evelocity_y*elapsed.asSeconds()));
                }
            }
        }
        else
        {
            move(0,evelocity_y*elapsed.asSeconds());
            for (auto &r:walls){
                if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
                {
                    move(0,-abs(evelocity_y*elapsed.asSeconds()));
                }
            }
        }
    }
    else if(pl_position.y<e_position.y)
    {
        if(pl_position.x>e_position.x)
        {
            move(evelocity_x*elapsed.asSeconds(),-abs(evelocity_y*elapsed.asSeconds()));
            for (auto &r:walls){
                if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
                {
                    move(-abs(evelocity_x*elapsed.asSeconds()),abs(evelocity_y*elapsed.asSeconds()));
                }
            }
        }
        else if(pl_position.x<e_position.x)
        {
            move(-abs(evelocity_x*elapsed.asSeconds()),-abs(evelocity_y*elapsed.asSeconds()));
            for (auto &r:walls){
                if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
                {
                    move(abs(evelocity_x*elapsed.asSeconds()),abs(evelocity_y*elapsed.asSeconds()));
                }
            }
        }
        else
        {
            move(0,-abs(evelocity_y*elapsed.asSeconds()));
            for (auto &r:walls){
                if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
                {
                    move(0,abs(evelocity_y*elapsed.asSeconds()));
                }
            }
        }
    }
    else
    {
        if(pl_position.x>e_position.x)
        {
            move(evelocity_x*elapsed.asSeconds(),0);
            for (auto &r:walls){
                if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
                {
                    move(-abs(evelocity_x*elapsed.asSeconds()),0);
                }
        }
        }
        else if(pl_position.x<e_position.x)
        {
            move(-abs(evelocity_x*elapsed.asSeconds()),0);
            for (auto &r:walls){
                if(r.getGlobalBounds().intersects(this->getGlobalBounds()))
                {
                    move(abs(evelocity_x*elapsed.asSeconds()),0);
                }
        }
        }
        else
        {
            move(0,0);
        }
    }
}


void Enemy::looking(AnimatedSprite pl)
{
    pl_position = pl.getPosition();
    const float PI=3.14159265;
    float mx=this->getPosition().x-pl_position.x;
    float my=this->getPosition().y-pl_position.y;
    float rot=atan2(my,mx)*180/PI+270;
    this->setRotation(rot);
}



