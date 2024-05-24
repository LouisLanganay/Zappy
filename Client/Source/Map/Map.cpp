/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#include "Map.hpp"

using namespace Zappy;

Map::Map() : mapVertices(sf::Quads, 100)
{
}

void Map::update(const std::string &data)
{
}

const sf::Drawable& Map::getDrawable() const
{
    return mapVertices;
}
