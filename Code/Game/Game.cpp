#include "Game.hpp"
#include "iostream"

Game::Game()
{
    srand(time(NULL)); // To get new alea number at each lauching

    gameEngine = new GameEngine();
    gameOverEngine = new GameOverEngine();
    font.loadFromFile("ressources/font/SuperMarioBros-ov7d.ttf");

    camera = new Camera();

    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "LOL");
    window->setFramerateLimit(60); // Block game at 60 FPS

    for (int i = 1; i < 6; i++)
    {
        flash[i - 1] = new SfmlImage("ressources/Images/maxresdefault.jpg", 1280, 720, 250 * i, 300);
        flash[i - 1]->getSprite().setScale(0.1, 0.1);

        textRebour[i - 1].setFont(font);
        textRebour[i - 1].setPosition(250 * i, 200);

        textTime[i - 1].setFont(font);
        textTime[i - 1].setPosition(250 * i, 400);

        isReady[i - 1] = true;
    }

    textRebour[0].setString("TOP");
    textRebour[1].setString("JUNGLER");
    textRebour[2].setString("MID");
    textRebour[3].setString("ADC");
    textRebour[4].setString("SUPPORT");

    // textTime[0].setString(std::to_string());
    textTime[1].setString("JUNGLER");
    textTime[2].setString("MID");
    textTime[3].setString("ADC");
    textTime[4].setString("SUPPORT");
}

std::string Game::getTime(int nbr)
{
    if (300 - timer[nbr].getElapsedTime().asSeconds() <= 0)
    {
        isReady[nbr] = true;
    }

    if (isReady[nbr])
    {
        flash[nbr]->getSprite().setColor(sf::Color(255, 255, 255));
        return "Ready";
    }

    flash[nbr]->getSprite().setColor(sf::Color(60, 60, 60));
    std::string o = std::to_string(300 - timer[nbr].getElapsedTime().asSeconds());
    std::string str = "";
    for (int i = 0; i < o.size(); i++)
    {
        if (o[i] == '.')
            break;

        str += o[i];
    }

    return str;
}

Game::~Game()
{
    delete window;
    delete gameEngine;
    delete gameOverEngine;
    delete camera;

    for (int i = 0; i < 5; i++)
    {
        delete flash[i];
    }
}

void Game::run()
{
    sf::Event event;

    // Window's Game
    while (window->isOpen())
    {

        // Check Event
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && !keyFup[0])
        {
            timer[0].restart();
            keyFup[0] = true;
            isReady[0] = !isReady[0];
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
        {
            keyFup[0] = false;
        }

        //

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2) && !keyFup[1])
        {
            timer[1].restart();
            keyFup[1] = true;
            isReady[1] = !isReady[1];
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        {
            keyFup[1] = false;
        }

        //

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3) && !keyFup[2])
        {
            timer[2].restart();
            keyFup[2] = true;
            isReady[2] = !isReady[2];
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
        {
            keyFup[2] = false;
        }

        //

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4) && !keyFup[3])
        {
            timer[3].restart();
            keyFup[3] = true;
            isReady[3] = !isReady[3];
        }

        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
        {
            keyFup[3] = false;
        }

        //

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5) && !keyFup[4])
        {
            timer[4].restart();
            keyFup[4] = true;
            isReady[4] = !isReady[4];
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
        {
            keyFup[4] = false;
        }

        //

        window->clear();

        for (int i = 0; i < 5; i++)
        {

            textTime[i].setString(getTime(i));

            flash[i]->draw(*window);
            window->draw(textRebour[i]);
            window->draw(textTime[i]);
        }

        window->display();

        // get the current mouse position in the window
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);

        // convert it to world coordinates
        sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
        // std::cout << worldPos.x << "   " << worldPos.y << "\n";
    }
}
