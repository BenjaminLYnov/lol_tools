#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
    // delete sprite;
}

void Actor::draw(sf::RenderWindow &window) const
{
    sprite->draw(window);
}

void Actor::performMovement(float deltaTime)
{
    gravity(deltaTime);
}

void Actor::gravity(float deltaTime)
{
    if (isOnGround)
        gravitySpeed = 0;
    else
        gravitySpeed += gravityForce;

    sprite->getSprite().move(0, gravitySpeed * deltaTime);
}