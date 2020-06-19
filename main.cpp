#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
#include <cstdlib>

#include "bullet.h"
#include "animatedsprite.h"
#include "enemy.h"


using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1300, 900), "My window");
    srand(time(NULL));

    //player
    sf::Texture tx_player;
    if(!tx_player.loadFromFile("texture/player.png")){return 1;}
    AnimatedSprite player;
    player.setScale(0.3,0.3);
    player.setTexture(tx_player);
    player.setTextureRect(sf::IntRect(10,10,200,200));
    player.setPosition(600,600);
    player.setOrigin(100,100);

    //background
    sf::Texture tx_metal;
    if(!tx_metal.loadFromFile("texture/metal.png")){return 2;}
    tx_metal.setRepeated(true);
    sf::Sprite metal;
    metal.setTexture(tx_metal);
    float scale=0.2;
    metal.setScale(scale,scale);
    metal.setTextureRect(sf::IntRect(0,0,window.getSize().x/scale,window.getSize().y/scale));

    //bullets
    Bullet b1;
    vector<Bullet> bullets;
    sf::Texture tx_bullet;
    //if(!tx_bullet.loadFromFile("texture/bullet.png")){return 3;}
    //else
    //{std::cout<<"loaded"<<std::endl;}
    //b1.Bullet::setTexture(tx_bullet);

    //wall
    sf::Texture tx_wall;
    if(!tx_wall.loadFromFile("texture/wall.png")){return 4;}
    tx_wall.setRepeated(true);
    sf::Sprite wall;
    wall.setTexture(tx_wall);
    wall.setTextureRect(sf::IntRect(0,0,500,500));

    vector<sf::Sprite> walls;
    int number_of_walls=4;
    for(auto i=0;i<number_of_walls;i++)
    {
        walls.emplace_back(AnimatedSprite());
    }
    for(auto &r:walls)
    {
        r.setTexture(tx_wall);
        r.setScale(0.5,0.5);
    }
    walls[0].setPosition(0,170);
    walls[0].setTextureRect(sf::IntRect(0,0,1200,100));
    walls[1].setPosition(600,170);
    walls[1].setTextureRect(sf::IntRect(0,0,100,700));
    walls[2].setPosition(800,700);
    walls[2].setTextureRect(sf::IntRect(0,0,100,800));
    walls[3].setPosition(250,400);
    walls[3].setTextureRect(sf::IntRect(0,0,100,1000));

    //enemy
    sf::Texture tx_enemy;
    sf::Sprite enemy;

    //enemy.settx(tx_enemy);
    if(!tx_enemy.loadFromFile("texture/enemy.png")){return 5;}
    enemy.setTexture(tx_enemy);
    enemy.setTextureRect(sf::IntRect(0,00,60,60));
    std::vector<sf::Sprite> enemies;
    int spawncounter=200;

    //enemy true
    Enemy enemy2;
    std::vector<Enemy> enemies2;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        player.rotating(window);
        player.animate(elapsed,walls);

        //b1.shooting(window,bullets,sf::Vector2f(player.getPosition().x,player.getPosition().y),walls,enemies);
        b1.shooting2(window,bullets,sf::Vector2f(player.getPosition().x,player.getPosition().y),walls,enemies2);

        if(spawncounter<800)
        {
            spawncounter++;
        }
        else if(spawncounter>=800&&enemies.size()<5)
        {
            //enemy.setPosition(sf::Vector2f(rand()%window.getSize().x,rand()%window.getSize().y));
            enemy2.setPosition(sf::Vector2f(rand()%window.getSize().x,rand()%window.getSize().y));
            //enemies.emplace_back(sf::Sprite(enemy));
            enemies2.emplace_back(Enemy(enemy2));
            spawncounter=0;
        }
        for(auto &r:enemies2)
        r.animate(elapsed,walls,player);


        //enemy.attack(window,enemies);

        //drawing
        window.draw(metal);
        for(auto i=0;i<bullets.size();i++)
        {
            window.draw(bullets[i].shape);
        }
        for(auto i=0;i<enemies.size();i++)
        {
            //window.draw(enemies[i]);
        }
        for(auto i=0;i<enemies2.size();i++)
        {
            window.draw(enemies2[i]);
        }

        window.draw(player);

        for(auto &r:walls)
        {
            window.draw(r);
        }


        window.display();

    }

    return 0;
}
