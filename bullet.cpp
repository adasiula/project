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
    damage=start_damage;

    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::Yellow);
};

