#ifndef INPUT_H
#define INPUT_H

#pragma once

#include "iostream"

class Input
{
public:
    Input();
    ~Input();

    static float GetAxisRaw(std::string axe);

private:
};

#endif