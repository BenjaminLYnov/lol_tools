#ifndef MOVE_H
#define MOVE_H

#pragma once

#include <SFML/Graphics.hpp>
#include "../Timer/Timer.hpp"

class Move
{
public:
	Move();
	~Move();

	void inputMove();
	void moveSprite(sf::Sprite &sprite, float speedMove);
	bool isMoving();

private:
	bool left;
	bool right;
};
#endif