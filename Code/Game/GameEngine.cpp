#include "GameEngine.hpp"
#include <string>
#include <iostream>
#include "../DataGame/Math/RandomNumber.hpp"
#include "../DataGame/Math/Vector2D.hpp"

template <typename T>
void checkGround(T &actor, Collider *collider)
{
    for (int j = 0; j < 10; j++)
    {
        actor.sprite->getSprite().move(0, 1);

        if (Collision::OnCollisionBySide("Up", actor.sprite->getSprite(), collider->getSprite(j)) ||
            Collision::OnCollisionBySide("Foot", actor.sprite->getSprite(), collider->getSprite(j)))
        {
            actor.isOnGround = true;
            actor.sprite->getSprite().move(0, -1);
            break;
        }
        else
        {
            actor.isOnGround = false;
        }
        actor.sprite->getSprite().move(0, -1);
    }
}

template <typename T>
void checkGround(std::vector<T> &actors, Collider *collider)
{
    for (int i = 0; i < actors.size(); i++)
    {
        for (int j = 0; j < 10; j++)
        {
            actors[i].sprite->getSprite().move(0, 1);

            if (Collision::OnCollisionBySide("Up", actors[i].sprite->getSprite(), collider->getSprite(j)) ||
                Collision::OnCollisionBySide("Foot", actors[i].sprite->getSprite(), collider->getSprite(j)))
            {
                actors[i].isOnGround = true;
                actors[i].sprite->getSprite().move(0, -1);
                break;
            }
            else
            {
                actors[i].isOnGround = false;
            }
            actors[i].sprite->getSprite().move(0, -1);
        }
    }
}

template <typename T>
void drawActors(const std::vector<T> &actors, sf::RenderWindow &window)
{
    for (int i = 0; i < actors.size(); i++)
        actors[i].draw(window);
}

GameEngine::GameEngine()
{
    map = new Map();
    mario = new Mario();
    collider = new Collider();
    uhd = new Uhd();

    init();
}

GameEngine::~GameEngine()
{
    delete map;
    delete mario;
    delete collider;
    delete uhd;
}

// Public functions

void GameEngine::draw(sf::RenderWindow &window) const
{
    // Draw Game

    map->Draw(window);
    drawActors(goombas, window);
    drawActors(shrooms, window);
    // drawActors(blocks, window);
    drawActors(coins, window);

    for (int i = 0; i < blocks.size(); i++)
    {
        // window.draw(blocks[i].hitbox->getSprite());
    }

    mario->draw(window);

    collider->draw(window);

    uhd->draw(window);
}

void GameEngine::run(float deltaTime)
{
    if (mario->isTransforming)
    {
        mario->transforming(deltaTime);
    }
    else if (!mario->isAlive)
    {
        mario->deathing(deltaTime);
    }
    else
    {
        // Update Game Logic
        update(deltaTime);

        // Move Actors
        performActorsMovement(deltaTime);

        // Collision step
        collisionStep();
    }
}

sf::Vector2f GameEngine::getMarioPosition()
{
    return mario->getSprite().getPosition();
}

// Private Functions

// Initiation

void GameEngine::init()
{
    goombas.push_back(Goomba({sf::Vector2f(400, 1040), sf::Vector2f(900, 1040)}));
    goombas.push_back(Goomba({sf::Vector2f(970, 945), sf::Vector2f(1200, 945)}));
    goombas.push_back(Goomba({sf::Vector2f(1410, 1040), sf::Vector2f(1600, 1040)}));
    goombas.push_back(Goomba(1, {sf::Vector2f(1600, 1040), sf::Vector2f(2000, 1040)}));

    blocks.push_back(Block());
    shrooms.push_back(Shroom());

    coins.push_back(Coin(500, 1000));
    coins.push_back(Coin(700, 1000));
}

// Update Game Logic
void GameEngine::update(float deltaTime)
{
    mario->update(deltaTime);
    shroomMarioPowerUp();
}

// Move actors
void GameEngine::performActorsMovement(float deltaTime)
{
    mario->performMovement(deltaTime);

    for (int i = 0; i < goombas.size(); i++)
        goombas[i].performMovement(deltaTime);

    for (int i = 0; i < shrooms.size(); i++)
        shrooms[i].performMovement(deltaTime);
}

// Collision Step
void GameEngine::collisionStep()
{
    // Check if actors is on ground, if true =>reset gravity speed to 0
    checkActorOnGround();

    headOnBlock();

    // Jump on goombas
    marioRebondOnEnnemie();

    marioGetHurt();
    marioCollisionOnCoin();

    changeShroomDirection();

    // Cancel collision
    collisionNotTrigger();
}

// Cancel gravity if actor is on ground
void GameEngine::checkActorOnGround()
{
    checkMarioJump();
    checkGround(shrooms, collider);
    checkGround(goombas, collider);
}

void GameEngine::headOnBlock()
{
    for (int i = 0; i < 10; i++)
    {
        if (Collision::OnCollisionBySide("Up", mario->getSprite(), collider->getSprite(i)))
        {
            mario->jump.setJumpSpeed(0);
            break;
        }
    }
}

void GameEngine::checkMarioJump()
{
    for (int i = 0; i < 10; i++)
    {
        mario->getSprite().move(0, 1);

        if (Collision::OnCollisionBySide("Down", mario->getSprite(), collider->getSprite(i)))
        {
            mario->jump.setJumpSpeed(0);
        }

        if (Collision::OnCollisionBySide("Up", mario->getSprite(), collider->getSprite(i)))
        {
            mario->setCanJump(true);
            mario->jump.setJumpSpeed(0);
            mario->gravitySpeed = 0;
            break;
        }
        else
        {
            mario->setCanJump(false);
        }
        mario->getSprite().move(0, -1);
    }

    // if (Collision::PixelPerfectTest(mario->footHitbox[0]->getSprite(), collider->getSprite(2)) ||
    //     Collision::PixelPerfectTest(mario->footHitbox[1]->getSprite(), collider->getSprite(2)))
    // {
    //     mario->setCanJump(true);
    //     mario->jump.setJumpSpeed(0);
    //     mario->gravitySpeed = 0;
    // }
}

// Cancel collision
void GameEngine::collisionNotTrigger()
{
    // for (int i = 0; i < blocks.size(); i++)
    //     Collision::NotTrigger(mario->getSprite(), blocks[i].sprite->getSprite());

    collider->notTrigger(mario->getSprite());

    // for (int j = 0; j < 10; j++)
    // {
    //     while (Collision::PixelPerfectTest(mario->getSprite(), collider->getSprite(j)))
    //     {
    //         mario->getSprite().move(-Vector2D::Normalized(mario->velocity) * 4.0f);
    //     }
    // }

    for (int i = 0; i < shrooms.size(); i++)
        collider->notTrigger(shrooms[i].sprite->getSprite());

    for (int i = 0; i < goombas.size(); i++)
        if (goombas[i].hp > 0)
            collider->notTrigger(goombas[i].sprite->getSprite());
}

// Mario jump on ennemie
void GameEngine::marioRebondOnEnnemie()
{
    // if (Collision::PixelPerfectTest(mario->getSprite(), goombas[i]Sprite))
    // {
    //     if (mario->getSprite().getPosition().y < goombas[i]Sprite.getPosition().y)
    //     {
    //         mario->jump.setJumpSpeed(1);
    //         mario->gravitySpeed = 0;
    //         mario->kickSound->sound.play();
    //         goombas[i].hp--;

    //         if (RandomNumber::RandomInt(0, 1) == 0)
    //             goombas[i].deathLeft = false;
    //     }
    // }

    for (int i = 0; i < goombas.size(); i++)
        if (goombas[i].hp > 0)
            if (Collision::PixelPerfectTest(mario->getSprite(), goombas[i].sprite->getSprite()))
            {
                if (mario->getSprite().getPosition().y < goombas[i].sprite->getSprite().getPosition().y)
                {
                    mario->jump.setJumpSpeed(0.7);
                    mario->gravitySpeed = 0;
                    mario->kickSound->sound.play();
                    goombas[i].hp--;

                    if (RandomNumber::RandomInt(0, 1) == 0)
                        goombas[i].deathLeft = false;
                }
            }

    // marioRebondOngoombas[i]s(goombas, mario);
}

// Power down mario on collision with ennemie
void GameEngine::marioGetHurt()
{
    if (mario->currentInvulnerableTime == 0)
        for (int i = 0; i < goombas.size(); i++)
            if (goombas[i].hp > 0)
                if (Collision::PixelPerfectTest(mario->getSprite(), goombas[i].sprite->getSprite()))
                    mario->powerDown();
}

void GameEngine::marioCollisionOnCoin()
{
    for (int i = 0; i < coins.size(); i++)
        if (Collision::PixelPerfectTest(mario->getSprite(), coins[i].sprite->getSprite()))
        {
            coins.erase(coins.begin() + i);
            coins[i].coinSound->sound.play();
            uhd->nbrCoin++;
        }
}

void GameEngine::shroomMarioPowerUp()
{
    for (int i = 0; i < shrooms.size(); i++)
        if (Collision::PixelPerfectTest(mario->getSprite(), shrooms[i].sprite->getSprite()))
        {
            shrooms.erase(shrooms.begin() + i);
            mario->powerUp();
        }
}

void GameEngine::changeShroomDirection()
{
    for (int i = 0; i < shrooms.size(); i++)
        for (int j = 0; j < 10; j++)
        {
            if (Collision::OnCollisionBySide("Left", shrooms[i].sprite->getSprite(), collider->getSprite(j)) ||
                Collision::OnCollisionBySide("Right", shrooms[i].sprite->getSprite(), collider->getSprite(j)))
            {
                shrooms[i].changeDirection();
                break;
            }
        }
}
