#include "SfmlImage.hpp"

SfmlImage::SfmlImage()
{
}

SfmlImage::SfmlImage(std::string scr, int dimX, int dimY)
{
     texture.loadFromFile(scr, sf::IntRect(0, 0, dimX, dimY));
     sprite.setTexture(texture);
}

SfmlImage::SfmlImage(std::string scr, int dimX, int dimY, double posX, double posY)
{
     texture.loadFromFile(scr, sf::IntRect(0, 0, dimX, dimY));
     sprite.setTexture(texture);
     sprite.setPosition(posX, posY);
}

SfmlImage::~SfmlImage()
{
}

sf::Sprite &SfmlImage::getSprite()
{
     return sprite;
}

void SfmlImage::draw(sf::RenderWindow &window) const
{
     window.draw(sprite);
}

void SfmlImage::SetCentralOrigin()
{
     sprite.setOrigin(abs(sprite.getTextureRect().width / 2), abs(sprite.getTextureRect().height / 2));
     // sprite.setOrigin(abs((sprite.getTextureRect().width * sprite.getScale().x) / 2), abs((sprite.getTextureRect().height * sprite.getScale().y) / 2));
}
