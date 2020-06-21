#include "bullet.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <math.h>
#include <iostream>
#include <vector>

#include "enemy.h"
#include "animatedsprite.h"

Bullet::Bullet(float radius)
{
    velocity_bullet=sf::Vector2f(0.0,0.0);
    maxspeed=start_maxspeed;
    speedshoot=start_speedshoot;//700;
    damage=start_damage;

    this->shape_bullet.setRadius(radius);
    this->shape_bullet.setFillColor(sf::Color::Yellow);

    if(!shoot_buffer.loadFromFile("sound/shoot.ogg")){std::cout<<"not loaded\n";};
    shoot.setBuffer(shoot_buffer);
};

