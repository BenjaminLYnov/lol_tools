#include "Collider.h"
#include "../Collision/Collision.h"

#include "iostream"

Collider::Collider()
{
    initBox();
}

Collider::~Collider()
{
}

// Public Functions

sf::Sprite &Collider::getSprite(int index) const
{
    return box[index].getSprite();
}

void Collider::notTrigger(sf::Sprite &sprite)
{
    for (int i = 0; i < NBR_COLLIDER; i++)
    {
        if (box[i].collisionType == All)
            Collision::NotTrigger(sprite, box[i].getSprite());
        else if (box[i].collisionType == Up)
            Collision::NotTriggerBySide("Up", sprite, box[i].getSprite());
        else if (box[i].collisionType == Left)
            Collision::NotTriggerBySide("Left", sprite, box[i].getSprite());
        else if (box[i].collisionType == Down)
            Collision::NotTriggerBySide("Down", sprite, box[i].getSprite());
        else if (box[i].collisionType == Right)
            Collision::NotTriggerBySide("Right", sprite, box[i].getSprite());
        else if (box[i].collisionType == Foot)
            Collision::NotTriggerBySide("Foot", sprite, box[i].getSprite());
    }
}

void Collider::draw(sf::RenderWindow &window) const
{
    for (int i = 0; i < NBR_COLLIDER; i++)
        box[i].draw(window);
}

// Private Functions

void Collider::initBox()
{
    setBox(0, 0, 1057, 10000, 2, 0, All);
    // setBox(0, 0, 1057, 10, 2, 0, All);
    setBox(1, 960, 960, 3.2, 2, 0, All);
    setBox(2, 315, 1005, 0.45, 0.1, -45, Foot);
    setBox(3, 000, 970, 0.5, 0.5, 0, All);
    setBox(4, 100, 970, 0.5, 0.5, 0, All);
}

void Collider::setBox(int index, int x, int y, float scaleX, float scaleY, float rotation, int collisionType)
{
    box[index].getSprite().setRotation(rotation);
    box[index].getSprite().setScale(scaleX, scaleY);
    box[index].getSprite().setPosition(x + box[index].getSprite().getTextureRect().width / 2 * box[index].getSprite().getScale().x, y + box[index].getSprite().getTextureRect().height / 2 * box[index].getSprite().getScale().y);
    box[index].collisionType = collisionType;
}
