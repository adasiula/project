#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "animatedsprite.h"
class AnimatedSprite;
#include "bullet.h"

class Enemy:public sf::Sprite//,sf::Drawable
{
public:
    Enemy();
    void attack(AnimatedSprite pl,sf::Time &elapsed,std::vector<sf::Sprite> &walls);
    void looking(AnimatedSprite pl);

    float enemycounter;
    int timespawn;
    sf::Vector2f pl_position;
    sf::Vector2f e_position;
    float life;
    float start_life=3;
private:
    float bounds_left_ = 0;
    float bounds_right_ = 1300;
    float bounds_top_ = 0;
    float bounds_bottom_ = 900;

    float evelocity_x=100;
    float evelocity_y=100;
};

#endif // ENEMY_H
