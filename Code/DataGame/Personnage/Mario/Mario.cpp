#include "Mario.hpp"
#include "../../../System/Input.h"

Mario::Mario()
{
     // Init mario sprite
     marioSprite = new SfmlImage("ressources/Mario/SNES - Super Mario World - Mario.png", 1004, 3618, 200, 1050);
     marioSprite->getSprite().setTextureRect(sf::IntRect(24, 51, 16, 22));
     marioSprite->getSprite().setScale(2, 2);
     // marioSprite->getSprite().setScale(4, 4);
     marioSprite->SetCentralOrigin();

     // Init foot hitbox
     for (int i = 0; i < 2; i++)
     {
          footHitbox[i] = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 0, 0);
          footHitbox[i]->SetCentralOrigin();
          footHitbox[i]->getSprite().setTextureRect(sf::IntRect(0, 0, 5, 5));
     }

     hitbox = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 0, 0);
     hitbox->SetCentralOrigin();

     // Sound
     jumpSound = new SfmlAudio("ressources/Sound/Snes Mario World/jump.wav");
     powerupSound = new SfmlAudio("ressources/Sound/Snes Mario World/powerup.wav");
     pipeSound = new SfmlAudio("ressources/Sound/Snes Mario World/pipe.wav");
     kickSound = new SfmlAudio("ressources/Sound/Snes Mario World/kick.wav");
     deadSound = new SfmlAudio("ressources/Sound/Video Game Deaths Super Mario World (SNES) (Death AnimationGame Over).wav");

     // For Wraparound
     onceTimeLeft = true;
     onceTimeRight = true;

     setSmallMario();
}

Mario::~Mario()
{
     delete jumpSound;
     delete powerupSound;
     delete kickSound;
     delete pipeSound;
     delete deadSound;
     delete marioSprite;
     delete hitbox;
}

void Mario::draw(sf::RenderWindow &window) const
{
     // std::cout << marioSprite->getSprite().getTextureRect().width << "\t" << marioSprite->getSprite().getTextureRect().height << "\n";
     // std::cout << marioSprite->getSprite().getTextureRect() << "\t" << marioSprite->getSprite().getTexture()->getSize().y << "\n";
     // std::cout << marioSprite->getSprite().getGlobalBounds() << "\t" << marioSprite->getSprite().getGlobalBounds() << "\n";
     // std::cout << marioSprite->getSprite().getTexture()->getSize().x << "\t" << marioSprite->getSprite().getTexture()->getSize().y << "\n";
     // std::cout << marioSprite->getSprite().getOrigin().x << "\t" << marioSprite->getSprite().getOrigin().y << "\t" << marioSprite->getSprite().getPosition().x << "\t" << marioSprite->getSprite().getPosition().y << "\n";
     // std::cout << marioSprite->getSprite().getPosition().x << "\t" << marioSprite->getSprite().getPosition().y << "\t       " << hitbox->getSprite().getPosition().x << "\t" << hitbox->getSprite().getPosition().y << "\n";
     marioSprite->draw(window);
     // hitbox->draw(window);

     // for (int i = 0; i < 2; i++)
     //   footHitbox[i]->draw(window);
}

void Mario::update(float deltaTime)
{
     setPositionFootHitbox();
     wraparound();
     switchState(deltaTime);

     invulnerable(deltaTime);

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
     {
          transformationMario(SmallMario);
          pipeSound->sound.play();
     }

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
     {
          transformationMario(SuperMario);
          powerupSound->sound.play();
     }

     hitbox->getSprite().setTextureRect(sf::IntRect(0, 0, marioSprite->getSprite().getTextureRect().width, marioSprite->getSprite().getTextureRect().height));
     hitbox->SetCentralOrigin();
     hitbox->getSprite().setPosition(marioSprite->getSprite().getPosition());
}

void Mario::performMovement(float deltaTime)
{
     if (state == MOVE || state == JUMP || state == FALLING)
     {
          float xMov = Input::GetAxisRaw("Horizontal") * speedMove * deltaTime;
          float yMov = -jump.jumpSpeed * deltaTime;

          velocity.x = xMov;
          velocity.y = yMov;

          marioSprite->getSprite().move(xMov, yMov);
          setPositionFootHitbox();
     }

     gravity(deltaTime);
     // getSprite().move(0, 1);

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
     {
          getSprite().move(0, -2);
          gravitySpeed = 0;
          std::cout << getSprite().getPosition().x << "\t" << getSprite().getPosition().y << "\n";
     }
}

void Mario::deathing(float deltaTime)
{
     currendDeathingTime += deltaTime;
     if (currendDeathingTime >= maxDeathingTime)
     {
          getSprite().move(0, -jump.jumpSpeed);
          jump.jumpSpeed -= 0.2;
     }
}

void Mario::gravity(float deltaTime)
{
     if (canJump)
          gravitySpeed = 0;
     else
          gravitySpeed += gravityForce;
     marioSprite->getSprite().move(0, gravitySpeed * deltaTime);
     velocity.y += gravitySpeed;
}

// Transformation
void Mario::transformationMario(int transfo)
{
     isTransforming = true;

     if (SmallMario == transfo)
          newTransformation = SmallMario;

     switch (transfo)
     {
     case SmallMario:
          newTransformation = SmallMario;
          break;
     case SuperMario:
          newTransformation = SuperMario;
          break;
     case FireMario:
          newTransformation = FireMario;
          break;
     }
}

void Mario::setCanJump(bool jump)
{
     canJump = jump;
}

void Mario::setJumpSpeed(float jumpSpeed)
{
     // this->jumpSpeed = jumpSpeed;
}

// Get Mario sprite
sf::Sprite &Mario::getSprite()
{
     return marioSprite->getSprite();
}

sf::Vector2f &Mario::getVelocity()
{
     return velocity;
}

// Private function

void Mario::setSmallMario()
{
     previousTransformation = transformation;
     transformation = SmallMario;
}

void Mario::setSuperMario()
{
     previousTransformation = transformation;
     transformation = SuperMario;
}

void Mario::invulnerable(float deltaTime)
{
     if (currentInvulnerableTime > 0)
          currentInvulnerableTime += deltaTime;

     if (currentInvulnerableTime >= maxInvulnerableTime)
     {
          currentInvulnerableTime = 0;
          getSprite().setColor(sf::Color(255, 255, 255, 255));
     }

     if (currentInvulnerableTime % 4 == 0)
          getSprite().setColor(sf::Color(255, 255, 255, 255));
     else
          getSprite().setColor(sf::Color(255, 255, 255, 0));
}

void Mario::transforming(float deltaTime)
{
     if (isTransforming)
     {
          transformationTimer += deltaTime;

          if ((int)(transformationTimer) % 30 == 0)
          {
               if (transformation == SmallMario)
                    marioSprite->getSprite().move(0, 15);
               else if (transformation == SuperMario)
                    marioSprite->getSprite().move(0, -3);

               marioSprite->getSprite().setTextureRect(sf::IntRect(24, 51, 16, 22));
          }
          else
          {
               if (transformation == SmallMario)
                    marioSprite->getSprite().move(0, -15);
               else if (transformation == SuperMario)
                    marioSprite->getSprite().move(0, 3);

               marioSprite->getSprite().setTextureRect(sf::IntRect(24, 586, 16, 30));
          }

          if (transformationTimer > 500)
          {
               isTransforming = false;
               transformationTimer = 0;
               transformation = newTransformation;
          }

          // if (transformation == SuperMario && previousTransformation == SmallMario) {
          // }
     }
}

void Mario::powerUp()
{
     if (transformation == SmallMario)
     {
          transformationMario(SuperMario);
          powerupSound->sound.play();
     }
}

void Mario::powerDown()
{
     if (transformation == SmallMario)
     {
          jump.jumpSpeed = 10;
          isAlive = false;
          deadSound->sound.play();
          marioSprite->getSprite().setTextureRect(sf::IntRect(544, 266, 16, 25));
     }
     else if (transformation == SuperMario)
     {
          pipeSound->sound.play();
          transformationMario(SmallMario);
          currentInvulnerableTime = 1;
     }
}

// State Function

void Mario::switchState(float deltaTime)
{
     switch (state)
     {
     case IDLE:
          setIdle();
          setStateJump();
          setStateMoving();
          setStateDunk();
          break;

     case MOVE:
          animationWalk(deltaTime);
          setStateJump();
          setStateDunk();
          if (Input::GetAxisRaw("Horizontal") == 0)
               setIdle();
          break;

     case JUMP:
          jumping(deltaTime);
          break;

     case FALLING:
          wraparound();
          if (canJump)
               setStateIdle();
          break;

     case DUNK:
          setDuck();
          break;
     }
}

// Fcutnions set State

void Mario::setStateIdle()
{
     previousState = state;
     state = IDLE;
}

void Mario::setStateMoving()
{
     if (Input::GetAxisRaw("Horizontal") != 0)
     {
          previousState = state;
          state = MOVE;
     }
}

void Mario::setStateJump()
{
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isSpace && canJump)
     {
          previousState = state;
          state = JUMP;
          jumpSound->sound.play();
          canJump = false;
          isSpace = false;
          jump.initJumpSpeed();
     }
     else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
          isSpace = true;
}

void Mario::setStateDunk()
{
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
     {
          previousState = state;
          state = DUNK;
     }
}

void Mario::setIdle()
{
     if (transformation == SmallMario)
          marioSprite->getSprite().setTextureRect(sf::IntRect(24, 51, 16, 22));
     else if (transformation == SuperMario)
          marioSprite->getSprite().setTextureRect(sf::IntRect(24, 586, 16, 30));
}

void Mario::setDuck()
{
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
     {
          // if (previousState == Moving && dunkTime.getTime() < 0.3)
          // {
          //      dunkTime.upTime();

          //      if (orientation == 1)
          //           moveDir.x = 1;

          //      else if (orientation == 0)
          //           moveDir.x = -1;
          // }

          if (transformation == SmallMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(128, 51, 16, 22));
          else if (transformation == SuperMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(128, 586, 16, 30));
     }
     else
     {
          // isDuckingDash = false;
          setStateIdle();
          // dunkTime.reset();
     }
}

void Mario::animationWalk(float deltaTime)
{
     if (transformation == SmallMario)
          animationSmallWalk(deltaTime);
     else if (transformation == SuperMario)
          animationSuperWalk(deltaTime);
}

void Mario::animationSmallWalk(float deltaTime)
{
     animationMoveTimer += deltaTime;

     if (animationMoveTimer > 200)
          animationMoveTimer = 0;
     else if (animationMoveTimer > 100)
          marioSprite->getSprite().setTextureRect(sf::IntRect(181, 51, 16, 22));
     else if (animationMoveTimer > 0)
          marioSprite->getSprite().setTextureRect(sf::IntRect(24, 51, 16, 22));
}

void Mario::animationSuperWalk(float deltaTime)
{
     animationMoveTimer += deltaTime;

     if (animationMoveTimer > 300)
          animationMoveTimer = 0;
     else if (animationMoveTimer > 200)
          marioSprite->getSprite().setTextureRect(sf::IntRect(179, 586, 18, 30));
     else if (animationMoveTimer > 100)
          marioSprite->getSprite().setTextureRect(sf::IntRect(232, 586, 17, 30));
     else if (animationMoveTimer > 0)
          marioSprite->getSprite().setTextureRect(sf::IntRect(24, 586, 16, 30));
}

void Mario::wraparound()
{
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && onceTimeLeft)
     {
          // orientation = 0;
          onceTimeLeft = false;
          onceTimeRight = true;
          marioSprite->getSprite().setPosition(marioSprite->getSprite().getPosition().x - (marioSprite->getSprite().getTextureRect().width * marioSprite->getSprite().getScale().x) * 1 / 2, marioSprite->getSprite().getPosition().y);
          marioSprite->getSprite().setScale(abs(getSprite().getScale().x), abs(getSprite().getScale().y));
          // marioSprite->getSprite().move(marioSprite->getSprite().getTextureRect().width * marioSprite->getSprite().getScale().x / 2, 0);
          // marioSprite->getSprite().setPosition(marioSprite->getSprite().getPosition().x - marioSprite->getSprite().getTextureRect().width * 1 / 2, marioSprite->getSprite().getPosition().y);
     }
     else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && onceTimeRight)
     {
          // orientation = 1;
          onceTimeLeft = true;
          onceTimeRight = false;
          marioSprite->getSprite().setPosition(marioSprite->getSprite().getPosition().x + marioSprite->getSprite().getTextureRect().width * 1 / 2, marioSprite->getSprite().getPosition().y);
          marioSprite->getSprite().setScale(-abs(getSprite().getScale().x), abs(getSprite().getScale().y));
          // marioSprite->getSprite().setPosition(marioSprite->getSprite().getPosition().x + (marioSprite->getSprite().getTextureRect().width * marioSprite->getSprite().getScale().x) * 1 / 2, marioSprite->getSprite().getPosition().y);
          // marioSprite->getSprite().move(-marioSprite->getSprite().getTextureRect().width * marioSprite->getSprite().getScale().x / 2, 0);
     }
}

void Mario::jumping(float deltaTime)
{
     // Set sprite anime
     if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
     {
          // Sprite Jump
          if (transformation == SmallMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(75, 112, 17, 42));
          else if (transformation == SuperMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(75, 654, 18, 32));
     }
     else
     {
          // Sprite Dunk
          if (transformation == SmallMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(128, 51, 16, 22));
          else if (transformation == SuperMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(128, 586, 16, 30));
     }

     // Jump highter
     // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
     //      maxJumpTime = 300;

     jump.updateJumpSpeed();

     // Jump End
     if (jump.jumpSpeed <= 0 || canJump)
     {
          jump.setJumpSpeed(0);
          previousState = state;
          if (canJump)
          {
               setIdle();
               setStateIdle();
          }
          else
               state = FALLING;
     }
}

void Mario::setPositionFootHitbox()
{
     if (state == IDLE || state == MOVE || state == DUNK)
     {
          footHitbox[0]->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 50, marioSprite->getSprite().getPosition().y + 65);
          footHitbox[1]->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 65);
     }
     else if (state == JUMP)
     {
          footHitbox[0]->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 50, marioSprite->getSprite().getPosition().y + 80);
          footHitbox[1]->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 80);
     }
}