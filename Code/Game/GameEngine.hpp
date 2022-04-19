#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#pragma once

#include "../DataGame/DataGame.hpp"
// #include <vector>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void run(float deltaTime);

	void draw(sf::RenderWindow &window) const;

	sf::Vector2f getMarioPosition();

	Map *map;
	Mario *mario;
	Uhd *uhd;

private:
	Collider *collider;


	std::vector<Block> blocks;
	std::vector<Shroom> shrooms;
	std::vector<Goomba> goombas;
	std::vector<Coin> coins;

	void init();

	void update(float deltaTime);

	void performActorsMovement(float deltaTime);

	void gravityStep(float deltaTime);


	// Collsion
	void collisionStep();
	void checkActorOnGround();
	void checkMarioJump();
	void headOnBlock();
	void marioRebondOnEnnemie();
	void marioGetHurt();
	void collisionNotTrigger();
	void marioCollisionOnCoin();

	// Shroom
	void shroomMarioPowerUp();
	void changeShroomDirection();
};
#endif