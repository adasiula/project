#ifndef BULLET_H
#define BULLET_H



#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "enemy.h"
class Enemy;
#include "animatedsprite.h"

class Bullet:public sf::Sprite,sf::RectangleShape
{
public:
    sf::CircleShape shape;
    sf::Vector2f currVelocity;
    float maxspeed;
    float start_maxspeed=3;
    int speedshoot;
    int start_speedshoot=450;
    int startdamage=1;
    int damage=0;

    Bullet(float radius=3.0);
    void shooting(sf::RenderWindow &w,std::vector<Bullet> &b,sf::Vector2f p,const std::vector<sf::Sprite> &walls,std::vector<Enemy> &en);
private:
    sf::Vector2f playercenter;
    sf::Vector2f mousepos;
    sf::Vector2f aimdir;
    sf::Vector2f aimdirnorm;
    int sp=0;
};

#endif // BULLET_H
