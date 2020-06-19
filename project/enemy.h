#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include<animatedsprite.h>
#include<bullet.h>
class Enemy:public sf::Sprite//,sf::Drawable
{
public:
    Enemy();
    void attack(sf::Window &w,std::vector<Enemy> &en);
    void settx(sf::Texture &tx);
    void animate(const sf::Time &elapsed,const std::vector<sf::Sprite> &walls,AnimatedSprite pl);
    //void setpos(float x1,float y1);
    int enemycounter=5;
    int timespawn=800;
};

#endif // ENEMY_H
