#ifndef MARIO_H
#define MARIO_H
#pragma once

#include "../../Actor/Actor.h"
#include "../../Timer/Timer.hpp"
#include "../../Collision/Collision.h"
#include "./Ability/Jump.h"

enum State
{
	IDLE,
	JUMP,
	FALLING,
	DUNK,
	MOVE,
};

enum Transformation
{
	SmallMario,
	SuperMario,
	FireMario,
};

class Mario
{
public:
	Mario();
	~Mario();

	void update(float deltaTime);
	void performMovement(float deltaTime);
	void draw(sf::RenderWindow &window) const;

	sf::Sprite &getSprite();
	sf::Vector2f &getVelocity();
	sf::Sprite *getFootHitbox();

	void gravity(float deltaTime);
	void setCanJump(bool jump);
	void setStateIdle();
	void setStateMoving();
	void setStateJump();
	void setStateDunk();
	void setJumpSpeed(float jumpSpeed);

	void setPositionFootHitbox();

	void powerDown();
	void powerUp();

	void deathing(float deltaTime);
	void invulnerable(float deltaTime);

	void transforming(float deltaTime);

	// Transformation
	void transformationMario(int transfo);

	float gravitySpeed = 0;
	float gravityForce = 0.03;

	float maxDeathingTime = 1000;
	float currendDeathingTime = 0;

	float maxInvulnerableTime = 1000; // 1 seconde
	int currentInvulnerableTime = 0;

	bool isTransforming = false;
	bool canJump = false;
	bool isAlive = true;

	Jump jump;

	SfmlImage *footHitbox[2];
	SfmlImage *hitbox;

	sf::Vector2f velocity;

	// Sound effect
	SfmlAudio *jumpSound;
	SfmlAudio *powerupSound;
	SfmlAudio *pipeSound;
	SfmlAudio *kickSound;
	SfmlAudio *deadSound;

private:
	State state = IDLE;
	State previousState = state;

	Transformation transformation = SmallMario;
	Transformation previousTransformation = transformation;
	Transformation newTransformation;

	bool onceTimeLeft;
	bool onceTimeRight;
	bool isMoving = false;
	bool isJumping = false;
	bool isSpace = true;
	bool isDucking = false;
	bool isDuckingDash = false;

	int size;
	int orientation = 1; // 		1 -> right     0 -> left
	float timeJump = 0.4;

	float speedMove = 0.4;

	// Sprite
	SfmlImage *marioSprite;

	Timer jumpTime;
	float dunkTime;
	float jumpTimer = 0;
	float animationMoveTimer;
	float transformationTimer;

	void checkState();
	void switchState(float deltaTime);

	void setIdle();

	void setSmallMario();
	void setSuperMario();

	void animationWalk(float deltaTime);
	void animationSmallWalk(float deltaTime);
	void animationSuperWalk(float deltaTime);

	void setDuck();
	void inputMove();

	void jumping(float deltaTime);
	void inputJump();

	void input();

	// Inverse mirror mario sprite
	void wraparound();

	bool keyW = true;
	bool keyX = true;
	bool keyC = true;
	bool keyV = true;
};
#endif