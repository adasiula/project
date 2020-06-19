#ifndef BULLET_H
#define BULLET_H

#include "enemy.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>





class Bullet:public sf::Sprite,sf::RectangleShape
{
public:
    sf::CircleShape shape;
    sf::Vector2f currVelocity;
    float maxspeed;
    int speedshoot;

    Bullet(float radius=3.0);
    void shooting(sf::RenderWindow &w,std::vector<Bullet> &b,sf::Vector2f p,const std::vector<sf::Sprite> &walls,std::vector<sf::Sprite> &enemies);
    void shooting2(sf::RenderWindow &w,std::vector<Bullet> &b,sf::Vector2f p,const std::vector<sf::Sprite> &walls,std::vector<Enemy> &en);

    //void shooting3(sf::RenderWindow &w,std::vector<Bullet> &b,sf::Vector2f p,const std::vector<sf::Sprite> &walls,std::vector<Enemy> &en);

    void settx(sf::Texture &tx);
private:
    sf::Vector2f playercenter;
    sf::Vector2f mousepos;
    sf::Vector2f aimdir;
    sf::Vector2f aimdirnorm;
    int sp=0;
};

#endif // BULLET_H
