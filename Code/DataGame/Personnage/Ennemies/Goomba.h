#ifndef GOOMBA_H
#define GOOMBA_H

#pragma once

#include "../../Actor/Actor.h"
#include "../../WayPoint/WayPoint.h"
#include <vector>

class Goomba : public Actor
{
public:
    Goomba();
    Goomba(std::vector<sf::Vector2f> pos);
    Goomba(float speedMove, std::vector<sf::Vector2f> pos);
    ~Goomba();


    void draw(sf::RenderWindow &window) const;

    void performMovement(float deltaTime);
    void gravity(float deltaTime);

    float speedMove = 0.1;

private:
    void init();
    void animationMove(float deltaTime);
    void initRect();
    float timerAnimation = 0;
    sf::IntRect rec[2][8];

    int indexX = 0;
    int indexY = 0;

    WayPoint wayPoint;
};

#endif