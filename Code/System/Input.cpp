#include "Input.h"
#include <SFML/Window/Keyboard.hpp>

Input::Input()
{
}

Input::~Input()
{
}

float Input::GetAxisRaw(std::string axe)
{
    if (axe == "Horizontal")
    {
        if (
            (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
            return 0;
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            return 1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            return -1;
    }
    else if (axe == "Vertical")
    {
        if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
            return 0;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return -1;
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            return 1;
    }
}