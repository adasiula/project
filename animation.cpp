#include "animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture,sf::Vector2u imagecount_,float switchtime_)
{
    this->imageCount=imagecount_;
    this->switchTime=switchtime_;
    totalTime=0.0f;
    currentImage.x=0;
    currentImage.y=0;

    uvRect.width=texture->getSize().x/float(imageCount.x);
    uvRect.height=texture->getSize().y/float(imageCount.y);
}

void Animation::update(float elapsed)
{
    totalTime+=elapsed;

    if(totalTime>=switchTime)
    {
        totalTime-=switchTime;
        currentImage.x++;
        std::cout<<currentImage.x<<" "<<currentImage.y<<std::endl;
        //currentImage.y++;
        if(currentImage.x>=imageCount.x)
        {
            currentImage.x=0;
            currentImage.y++;
        }
        if(currentImage.y==imageCount.y-1&&currentImage.x==imageCount.x-1)
        {
            currentImage.x=0;
            currentImage.y=0;
        }
    }
    uvRect.left=currentImage.x*uvRect.width;
    uvRect.top=currentImage.y*uvRect.height;
}



