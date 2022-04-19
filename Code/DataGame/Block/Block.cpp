#include "Block.h"

Block::Block()
{
    sprite = new SfmlImage("ressources/Images/51a70c410a2f1cf.png", 1200, 1200, 500, 1000);
    // sprite->getSprite().setScale(0.2, 0.2);
    sprite->getSprite().setScale(0.02, 0.02);
    sprite->SetCentralOrigin();

    hitbox = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 600, 1000);
    hitbox->SetCentralOrigin();
    hitbox->getSprite().setColor(sf::Color(12, 23, 56));
}

Block::~Block()
{
    // delete hitbox;
}

