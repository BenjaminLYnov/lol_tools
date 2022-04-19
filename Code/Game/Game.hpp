#ifndef GAME_H
#define GAME_H
#pragma once

#include "GameEngine.hpp"
#include "GameOverEngine.hpp"

#define WIDTH 1600
#define HEIGHT 1080

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	sf::RenderWindow *window;
	GameEngine *gameEngine;
	GameOverEngine *gameOverEngine;
	Camera *camera;

	SfmlImage *flash[5];

	sf::Clock timer[5];
	bool keyFup[5];
	bool isReady[5];

	float deltaTime = 0;
	float dtLogic = 15;
	float updateTime = 0;

	
    sf::Font font;
    sf::Text textRebour[5];
    sf::Text textTime[5];

	std::string getTime(int nbr);

	void update();
};
#endif