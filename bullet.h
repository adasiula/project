#ifndef BULLET_H
#define BULLET_H



#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "enemy.h"
class Enemy;
#include "animatedsprite.h"

class Bullet:public sf::Sprite//,sf::RectangleShape
{
public:
    sf::CircleShape shape_bullet;
    sf::Vector2f velocity_bullet;
    float maxspeed;
    float start_maxspeed=3;
    int speedshoot;
    int start_speedshoot=350;
    float start_damage=2;
    float damage=0;

    int sp=0;

    sf::SoundBuffer shoot_buffer;
    sf::Sound shoot;

    Bullet(float radius=3.0);
private:
};

#endif // BULLET_H
