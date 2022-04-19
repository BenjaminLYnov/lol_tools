#include "Move.hpp"

Move::Move()
{
     left = false;
     right = false;
}

Move::~Move()
{
}

void Move::inputMove()
{
     if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
          right = true;
     else
          right = false;

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
          left = true;
     else
          left = false;
}

void Move::moveSprite(sf::Sprite &sprite, float speedMove)
{
     if (left)
          sprite.move(-speedMove, 0);
     if (right)
          sprite.move(speedMove, 0);
}

bool Move::isMoving()
{
     if (left || right)
          return true;
     else
          return false;
}
