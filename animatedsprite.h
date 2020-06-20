#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "bullet.h"
class Bullet;
#include "enemy.h"
class Enemy;

class AnimatedSprite:public sf::Sprite
{
public:
    AnimatedSprite();
    void rotating(sf::RenderWindow &w);
    void animate(const sf::Time &elapsed,const std::vector<sf::Sprite> &walls);
    void shooting(sf::RenderWindow &w,std::vector<Bullet> &b,const std::vector<sf::Sprite> &walls,std::vector<Enemy> &en,Bullet &b1);

    int point=0;
private:
    float bounds_left_ = 0;
    float bounds_right_ = 1300;
    float bounds_top_ = 0;
    float bounds_bottom_ = 900;

    float velocity_x=300;
    float velocity_y=300;

    int sp=0;
};

#endif // ANIMATEDSPRITE_H
