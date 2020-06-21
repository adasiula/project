#include <iostream>
#include <memory>

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <sstream>

#include "bullet.h"
#include "animatedsprite.h"
#include "enemy.h"
#include "animation.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Shooter");
    srand(time(NULL));

    //player
    sf::Texture tx_player;
    if(!tx_player.loadFromFile("texture/player.png")){return 1;}
    AnimatedSprite player;
    player.setScale(0.3,0.3);
    player.setTexture(tx_player);
    player.setTextureRect(sf::IntRect(10,10,200,200));
    player.setPosition(window.getSize().x/2,window.getSize().y/2);
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


    //wall
    sf::Texture tx_wall;
    if(!tx_wall.loadFromFile("texture/wall.png")){return 4;}
    tx_wall.setRepeated(true);
    sf::Sprite wall;//130 na 130
    wall.setTexture(tx_wall);
    wall.setTextureRect(sf::IntRect(0,0,1000,1000));

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
    walls[0].setPosition(400,600);
    walls[0].setTextureRect(sf::IntRect(0,0,130,600));
    walls[1].setPosition(800,0);
    walls[1].setTextureRect(sf::IntRect(0,0,130,700));
    walls[2].setPosition(0,300);
    walls[2].setTextureRect(sf::IntRect(0,0,900,130));
    walls[3].setPosition(800,600);
    walls[3].setTextureRect(sf::IntRect(0,0,1100,130));

    //enemy
    sf::Texture tx_enemy;
    if(!tx_enemy.loadFromFile("texture/enemy.png")){return 5;}
    Enemy enemy;
    std::vector<Enemy> enemies;
    int spawncounter=enemy.timespawn;

    //texts
    std::string score="SCORE:";
    sf::Text mytext1;
    sf::Text mytext2;
    sf::Text mytext3;
    sf::Text mytext4;
    int life_counter=player.life;
    sf::Text mytext5;
    std::string health ="HEALTH:";
    std::vector<sf::Text> lifes;
    sf::Font font;
    if(!font.loadFromFile("fonts/font.ttf")){return 6;};

    mytext1.setPosition(window.getSize().x-200,30);
    mytext2.setPosition(window.getSize().x-80,30);

    //animation
    Animation animation(&tx_enemy,sf::Vector2u(3,3),0.3);

    //foot player animation


    //music
    sf::Music music;
    if(!music.openFromFile("sound/music.ogg")){return 7;};
    music.setVolume(50);
    music.setLoop(true);
    music.play();


    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        if(player.life<=0)
        {
            window.setActive(false);
            window.clear(sf::Color::Black);
            sf::Text gameover;
            std::string gm= "GAME OVER";
            gameover.setString(gm);
            gameover.setCharacterSize(100);
            gameover.setStyle(sf::Text::Bold);
            gameover.setFont(font);
            gameover.setFillColor(sf::Color::White);
            gameover.setPosition(350,350);
            window.draw(gameover);
            gameover.setString(score);
            gameover.setPosition(450,500);
            gameover.setCharacterSize(50);
            window.draw(gameover);
            std::stringstream result;
            result<<player.point;
            gameover.setString(result.str().c_str());
            gameover.setPosition(650,500);
            window.draw(gameover);
        }
        else
        {
        player.rotating(window);
        player.animate(elapsed,walls);
        player.shooting(window,bullets,walls,enemies,b1);

        //spawning enemies
        if(spawncounter<enemy.timespawn)
        {
            spawncounter++;
        }
        else if(spawncounter>=enemy.timespawn&&(int)enemies.size()<=enemy.enemycounter-1)
        {
            if(enemy.life<600)enemy.life+=1;
            if(enemy.life>30)enemy.setScale(1.3,1.3);
            if(enemy.life>40)enemy.setScale(1.6,1.6);
            enemy.enemycounter+=0.1;
            if(enemy.timespawn>300)enemy.timespawn-=5;
            enemy.setTexture(tx_enemy);
            int choose=rand()%4;
            switch(choose)
            {
            case 0:
            {
                enemy.setPosition(sf::Vector2f(window.getSize().x-30,window.getSize().y/2));break;
            }
            case 1:
            {
                enemy.setPosition(sf::Vector2f(30,window.getSize().y/2));break;
            }
            case 2:
            {
                enemy.setPosition(sf::Vector2f(window.getSize().x/2,30));break;
            }
            case 3:
            {
                enemy.setPosition(sf::Vector2f(window.getSize().x/2,window.getSize().y-30));break;
            }
            default:break;
            }
            enemies.emplace_back(enemy);
            spawncounter=0;
        }
        for(auto &r:enemies)
        {r.looking(player);
        r.attack(player,elapsed,walls);
        r.punch(player);}

        //update text
        mytext1.setString(score);
        mytext1.setCharacterSize(30);
        mytext1.setStyle(sf::Text::Bold);
        mytext1.setFont(font);
        mytext1.setFillColor(sf::Color::Red);

        std::stringstream ss;
        ss<<player.point;

        mytext2.setString(ss.str().c_str());
        mytext2.setCharacterSize(30);
        mytext2.setStyle(sf::Text::Bold);
        mytext2.setFont(font);
        mytext2.setFillColor(sf::Color::White);

        for(auto &r:enemies)
        {
            stringstream l;
            l<<r.life;
            mytext3.setString(l.str().c_str());
            mytext3.setCharacterSize(30);
            mytext3.setStyle(sf::Text::Bold);
            mytext3.setFont(font);
            mytext3.setFillColor(sf::Color::Red);
            mytext3.setPosition(r.getPosition().x,r.getPosition().y);
            lifes.emplace_back(mytext3);
        }

        life_counter=player.life;
        stringstream l2;
        l2<<life_counter;
        mytext4.setString(l2.str().c_str());
        mytext4.setCharacterSize(30);
        mytext4.setStyle(sf::Text::Bold);
        mytext4.setFont(font);
        if(player.life>21)mytext4.setFillColor(sf::Color::Green);
        else mytext4.setFillColor(sf::Color::Red);
        mytext4.setPosition(230,30);

        mytext5.setString(health);
        mytext5.setCharacterSize(30);
        mytext5.setStyle(sf::Text::Bold);
        mytext5.setFont(font);
        mytext5.setFillColor(sf::Color::White);
        mytext5.setPosition(30,30);

        //animations update
        for(auto &r:enemies)
        {
        animation.update(elapsed.asSeconds());
        r.setTextureRect(animation.uvRect);
        }
        //sound



        //drawing

        window.draw(metal);

        for(size_t i=0;i<bullets.size();i++)
        {
            window.draw(bullets[i].shape_bullet);
        }

        for(size_t i=0;i<enemies.size();i++)
        {
            window.draw(enemies[i]);
        }

        window.draw(player);

        for(auto &r:walls)
        {
            window.draw(r);
        }
        window.draw(mytext1);
        window.draw(mytext2);
        window.draw(mytext4);
        window.draw(mytext5);
        for(size_t i=0;i<lifes.size();i++)
        {
            window.draw(lifes[i]);
            lifes.erase(lifes.begin()+i);
        }
       }

        window.display();
    }

    return 0;
}
