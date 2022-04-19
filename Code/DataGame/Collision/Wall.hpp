#ifndef WALL_H
#define WALL_H
#pragma once

#include "Collision.h"
#include <SFML/Graphics.hpp>


class Wall
{
private:
public:
	Wall();
	~Wall();

	static void collisionNotTrigger(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void notTrigger(sf::Sprite &sprite1, sf::Sprite &sprite2, sf::Vector2f velocity);
	static sf::Vector2f getVectorMove(sf::Sprite &sprite1, sf::Sprite &sprite2);

	static void notTriggerLeft(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void notTriggerRight(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void notTriggerUp(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void notTriggerDown(sf::Sprite &sprite1, sf::Sprite &sprite2);


	static void collisionWall(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void collisionWallLeft(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void collisionWallRight(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void collisionWallUp(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void collisionWallDown(sf::Sprite &sprite1, sf::Sprite &sprite2);

	static bool collisionUp(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static bool collisionDown(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static bool collisionRight(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static bool collisionLeft(sf::Sprite &sprite1, sf::Sprite &sprite2);

	static void setPositionUp(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void setPositionDown(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void setPositionRight(sf::Sprite &sprite1, sf::Sprite &sprite2);
	static void setPositionLeft(sf::Sprite &sprite1, sf::Sprite &sprite2);

	static int getSide(sf::Sprite &sprite1, sf::Sprite &sprite2);

};
#endif