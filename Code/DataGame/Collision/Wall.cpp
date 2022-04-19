#include "Wall.hpp"
#include "../Math/Radius.hpp"
#include "../Math/Vector2D.hpp"
#include <cmath>
#include <iostream>

Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::notTrigger(sf::Sprite &sprite1, sf::Sprite &sprite2, sf::Vector2f velocity)
{
     while (Collision::PixelPerfectTest(sprite1, sprite2))
     {
          sprite1.move(getVectorMove(sprite1, sprite2));
     }
}

sf::Vector2f Wall::getVectorMove(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     // Get depth distance

     // Left
     float depthDistanceLeft = abs((sprite1.getPosition().x + sprite1.getTextureRect().width * sprite1.getScale().x / 2) - (sprite2.getPosition().x - sprite2.getTextureRect().width * sprite2.getScale().x / 2));

     // Right
     float depthDistanceRight = abs((sprite1.getPosition().x - sprite1.getTextureRect().width * sprite1.getScale().x / 2) - (sprite2.getPosition().x + sprite2.getTextureRect().width * sprite2.getScale().x / 2));

     // Up
     float depthDistanceUp = abs((sprite1.getPosition().y + sprite1.getTextureRect().height * sprite1.getScale().y / 2) - (sprite2.getPosition().y - sprite2.getTextureRect().height * sprite2.getScale().y / 2));

     // Down
     float depthDistanceDown = abs((sprite1.getPosition().y - sprite1.getTextureRect().height * sprite1.getScale().y / 2) - (sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2));

     // Search the less
     float minDepthDistance = depthDistanceUp;
     sf::Vector2f normalVector = sf::Vector2f(0, -1);

     if (minDepthDistance > depthDistanceDown)
     {
          minDepthDistance = depthDistanceDown;
          normalVector = sf::Vector2f(0, 1);
     }

     if (minDepthDistance >= depthDistanceLeft)
     {
          minDepthDistance = depthDistanceLeft;
          normalVector = sf::Vector2f(-1, 0);
     }

     if (minDepthDistance > depthDistanceRight)
     {
          minDepthDistance = depthDistanceRight;
          normalVector = sf::Vector2f(1, 0);
     }

     if (minDepthDistance >= depthDistanceUp || abs(minDepthDistance - depthDistanceUp) < 10)
     {
          minDepthDistance = depthDistanceUp;
          normalVector = sf::Vector2f(0, -1);
     }

     return normalVector;
}

void Wall::collisionNotTrigger(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     while (Collision::PixelPerfectTest(sprite1, sprite2))
     {
          sf::Vector2f vecNormal;
          sf::Vector2f rotation;

          int side = getSide(sprite1, sprite2);

          // Search the normal vector that will be used

          if (side == 0)
               vecNormal = sf::Vector2f(0, -1);
          else if (side == 1)
               vecNormal = sf::Vector2f(-1, 0);
          else if (side == 2)
               vecNormal = sf::Vector2f(0, 1);
          else
               vecNormal = sf::Vector2f(1, 0);

          // vecNormal.x = sprite2.getPosition().x - sprite2.getTextureRect().width / 2 - sprite2.getPosition().x + sprite2.getTextureRect().width / 2;
          // vecNormal.y = sprite2.getPosition().y - sprite2.getTextureRect().height / 2 - sprite2.getPosition().y - sprite2.getTextureRect().height / 2;

          // vecNormal = Vector2D::Normalized(vecNormal);

          if (sprite2.getRotation() != 0)
               vecNormal = sf::Vector2f(0, -1);

          // std::cout << vecNormal.x << " " << vecNormal.y << "\n";

          // Get Angle Normal Vector
          // rotation.x = (float)acos(vecNormal.x) * 180 / PI;
          // rotation.y = (float)asin(vecNormal.y) * 180 / PI;

          // Change rotation Vector Normal
          // vecNormal.x = (float)cos((rotation.x - sprite2.getRotation()) * PI / 180);
          // vecNormal.y = (float)sin((sprite2.getRotation() - rotation.y) * PI / 180);

          sprite1.move(vecNormal);
     }
}

int Wall::getSide(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     // 0 -> Up
     // 1 -> Left
     // 2 -> Down
     // 3 -> Right

     sf::Vector2f dir = sprite1.getPosition() - sprite2.getPosition();
     dir = Vector2D::Normalized(dir);

     // std::cout <<  dir.x << "  " << dir.y << "\n";

     if (fabs(dir.x) > fabs(dir.y))
          if (dir.x > 0)
               return 3;
          else
               return 1;
     else if (fabs(dir.x) < fabs(dir.y) || fabs(dir.x) == fabs(dir.y))
          if (dir.y < 0)
               return 0;
          else
               return 2;
}

void Wall::notTriggerUp(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     while (Collision::PixelPerfectTest(sprite1, sprite2))
     {
          sprite1.move(0, -1);
     }
}

void Wall::collisionWall(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (collisionUp(sprite1, sprite2))
          setPositionUp(sprite1, sprite2);
     if (collisionDown(sprite1, sprite2))
          setPositionDown(sprite1, sprite2);
     if (collisionRight(sprite1, sprite2))
          setPositionRight(sprite1, sprite2);
     if (collisionLeft(sprite1, sprite2))
          setPositionLeft(sprite1, sprite2);
}

void Wall::collisionWallUp(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (collisionUp(sprite1, sprite2))
          setPositionUp(sprite1, sprite2);
}

void Wall::collisionWallLeft(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (collisionLeft(sprite1, sprite2))
          setPositionLeft(sprite1, sprite2);
}

void Wall::collisionWallRight(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (collisionRight(sprite1, sprite2))
          setPositionRight(sprite1, sprite2);
}

void Wall::collisionWallDown(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (collisionDown(sprite1, sprite2))
          setPositionDown(sprite1, sprite2);
}

bool Wall::collisionUp(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (Collision::PixelPerfectTest(sprite1, sprite2) && sprite1.getPosition().y < sprite2.getPosition().y)
          return true;

     return false;

     // if (Collision::PixelPerfectTest(sprite1, sprite2))
     // {
     //      double radius;
     //      double cornerRadius;
     //      double bilateralRadius;
     //      double cornerRadiusUpLeft;
     //      double cornerRadiusUpRight;
     //      double cornerRadiusDownLeft;
     //      double cornerRadiusDownRight;
     //      cornerRadius = Radius::radiusCorner(sprite2);
     //      cornerRadiusUpLeft = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x, sprite1.getPosition().y);
     //      cornerRadiusUpRight = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x + sprite1.getTextureRect().width, sprite1.getPosition().y);
     //      cornerRadiusDownLeft = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x, sprite1.getPosition().y + sprite1.getTextureRect().height);
     //      cornerRadiusDownRight = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x + sprite1.getTextureRect().width, sprite1.getPosition().y + sprite1.getTextureRect().height);
     //      bilateralRadius = (360 - (cornerRadius * 4)) / 2;

     //      // Up
     //      if ((cornerRadiusDownLeft >= cornerRadius && cornerRadiusDownLeft <= (cornerRadius + bilateralRadius)) || (cornerRadiusDownRight >= cornerRadius && cornerRadiusDownRight <= (cornerRadius + bilateralRadius)))
     //           return true;
     // }
     // return false;
}

bool Wall::collisionDown(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (Collision::PixelPerfectTest(sprite1, sprite2))
     {
          double radius;
          double cornerRadius;
          double bilateralRadius;
          double cornerRadiusUpLeft;
          double cornerRadiusUpRight;
          double cornerRadiusDownLeft;
          double cornerRadiusDownRight;
          cornerRadius = Radius::radiusCorner(sprite2);
          cornerRadiusUpLeft = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x, sprite1.getPosition().y);
          cornerRadiusUpRight = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x + sprite1.getTextureRect().width, sprite1.getPosition().y);
          cornerRadiusDownLeft = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x, sprite1.getPosition().y + sprite1.getTextureRect().height);
          cornerRadiusDownRight = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x + sprite1.getTextureRect().width, sprite1.getPosition().y + sprite1.getTextureRect().height);
          bilateralRadius = (360 - (cornerRadius * 4)) / 2;

          // Down
          if ((cornerRadiusUpLeft >= (cornerRadius * 3 + bilateralRadius) && cornerRadiusUpLeft <= (cornerRadius * 3 + bilateralRadius * 2)) || (cornerRadiusUpRight >= (cornerRadius * 3 + bilateralRadius) && cornerRadiusUpRight <= (cornerRadius * 3 + bilateralRadius * 2)))
               return true;
     }
     return false;
}

bool Wall::collisionRight(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (Collision::PixelPerfectTest(sprite1, sprite2))
     {
          double radius;
          double cornerRadius;
          double bilateralRadius;
          double cornerRadiusUpLeft;
          double cornerRadiusUpRight;
          double cornerRadiusDownLeft;
          double cornerRadiusDownRight;
          cornerRadius = Radius::radiusCorner(sprite2);
          cornerRadiusUpLeft = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x, sprite1.getPosition().y);
          cornerRadiusUpRight = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x + sprite1.getTextureRect().width, sprite1.getPosition().y);
          cornerRadiusDownLeft = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x, sprite1.getPosition().y + sprite1.getTextureRect().height);
          cornerRadiusDownRight = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x + sprite1.getTextureRect().width, sprite1.getPosition().y + sprite1.getTextureRect().height);
          bilateralRadius = (360 - (cornerRadius * 4)) / 2;

          // Right
          if ((cornerRadiusUpLeft >= (cornerRadius * 3 + bilateralRadius * 2) || cornerRadiusUpLeft <= cornerRadius) || (cornerRadiusDownLeft >= (cornerRadius * 3 + bilateralRadius * 2) || cornerRadiusDownLeft <= cornerRadius))
               return true;
     }
     return false;
}

bool Wall::collisionLeft(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     if (Collision::PixelPerfectTest(sprite1, sprite2))
     {
          double radius;
          double cornerRadius;
          double bilateralRadius;
          double cornerRadiusUpLeft;
          double cornerRadiusUpRight;
          double cornerRadiusDownLeft;
          double cornerRadiusDownRight;
          cornerRadius = Radius::radiusCorner(sprite2);
          cornerRadiusUpLeft = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x, sprite1.getPosition().y);
          cornerRadiusUpRight = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x + sprite1.getTextureRect().width, sprite1.getPosition().y);
          cornerRadiusDownLeft = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x, sprite1.getPosition().y + sprite1.getTextureRect().height);
          cornerRadiusDownRight = Radius::radiusBeetween2Vector(sprite2.getPosition().x + sprite2.getTextureRect().width, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y / 2, sprite1.getPosition().x + sprite1.getTextureRect().width, sprite1.getPosition().y + sprite1.getTextureRect().height);
          bilateralRadius = (360 - (cornerRadius * 4)) / 2;

          // Left
          if ((cornerRadiusUpRight >= (cornerRadius + bilateralRadius) && cornerRadiusUpRight <= (cornerRadius * 3 + bilateralRadius)) || (cornerRadiusDownRight >= (cornerRadius + bilateralRadius) && cornerRadiusDownRight <= (cornerRadius * 3 + bilateralRadius)))
               return true;
     }
     return false;
}

void Wall::setPositionUp(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     sprite1.setPosition(sprite1.getPosition().x, sprite2.getPosition().y - sprite1.getTextureRect().height);
}

void Wall::setPositionDown(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     sprite1.setPosition(sprite1.getPosition().x, sprite2.getPosition().y + sprite2.getTextureRect().height * sprite2.getScale().y);
}

void Wall::setPositionRight(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     sprite1.setPosition(sprite2.getPosition().x + sprite2.getTextureRect().width * sprite2.getScale().x, sprite1.getPosition().y);
}

void Wall::setPositionLeft(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
     sprite1.setPosition(sprite2.getPosition().x - sprite1.getTextureRect().width, sprite1.getPosition().y);
}
