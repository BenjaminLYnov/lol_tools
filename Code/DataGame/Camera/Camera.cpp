#include "Camera.hpp"
#include "../Math/Vector2D.hpp"

Camera::Camera()
{
    camera = sf::View(sf::FloatRect(800, 540, -400, 1000));
    // camera.setSize(3000, 2040);
    camera.setSize(800, 540);

    speedMove = 30;
}

Camera::~Camera()
{
}

void Camera::update(sf::Vector2f playerPosition, float deltaTime)
{
    deltaTime /= 100;

    sf::Vector2f pourcentage = getPourcentageOnScreen(playerPosition);
    float distance = Vector2D::Distance(camera.getCenter(), playerPosition) / 100;

    if (pourcentage.x >= 60)
        camera.move(speedMove * deltaTime * distance, 0);
    else if (pourcentage.x <= 40)
        camera.move(-speedMove * deltaTime * distance, 0);

    if (pourcentage.y >= 60)
        camera.move(0, speedMove * deltaTime * distance);
    else if (pourcentage.y <= 40)
        camera.move(0, -speedMove * deltaTime * distance);
}

sf::Vector2f Camera::getPourcentageOnScreen(sf::Vector2f object)
{
    sf::Vector2f pourcentage;
    pourcentage.x = (object.x - camera.getCenter().x + camera.getSize().x / 2) * 100 / camera.getSize().x;
    pourcentage.y = (object.y - camera.getCenter().y + camera.getSize().y / 2) * 100 / camera.getSize().y;
    return pourcentage;
}

sf::View &Camera::getView()
{
    return camera;
}