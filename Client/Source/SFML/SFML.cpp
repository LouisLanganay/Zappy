/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SFML
*/

#include "SFML.hpp"

using namespace Zappy;

SFML::SFML()
    : window(
        sf::VideoMode(
            sf::VideoMode::getDesktopMode().width,
            sf::VideoMode::getDesktopMode().height
        ),
        "Zappy"
    )
{
}

SFML::~SFML()
{
}

void SFML::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void SFML::clear()
{
    window.clear();
}

void SFML::draw(const sf::Drawable& drawable)
{
    window.draw(drawable);
}

void SFML::display()
{
    window.display();
}

bool SFML::isOpen() const
{
    return window.isOpen();
}
