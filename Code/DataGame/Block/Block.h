#ifndef BLOCK_H
#define BLOCK_H

#pragma once
#include "../Actor/Actor.h"

class Block : public Actor
{
public:
    Block();
    ~Block();
    
	SfmlImage *hitbox;


private:
};

#endif