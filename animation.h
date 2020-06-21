#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(sf::Texture* texture,sf::Vector2u imagnecount,float switchtime);

    sf::IntRect uvRect;
    void update(float elapsed);
private:


    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};

#endif // ANIMATION_H
