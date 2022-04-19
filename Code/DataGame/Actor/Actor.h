#ifndef ACTOR_H
#define ACTOR_H

#pragma once

#include "../SFML/SfmlAudio.hpp"
#include "../SFML/SfmlImage.hpp"

class Actor
{
public:
    Actor();
    ~Actor();

    bool isOnGround = false;
    float speedMove;
    int hp = 1;
    bool deathLeft = true;
    SfmlImage *sprite;

    void draw(sf::RenderWindow &window) const;

    void gravity(float deltaTime);
    void performMovement(float deltaTime);

protected:
    float gravitySpeed = 0;
    float gravityForce = 0.03;
    float jumpSpeed = 1;

private:
};

#endif