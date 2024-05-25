/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#include "Map.hpp"

using namespace Zappy;

Map::Map()
{
    setSize(0, 0);
}

Map::~Map()
{
}

void Map::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
    tiles.resize(height, std::vector<Tile>(width));
    updateDrawable();
}

void Map::updateTile(int x, int y, const std::vector<int>& resources)
{
    if (x >= 0 && x < width && y >= 0 && y < height && resources.size() == 6) {
        tiles[y][x].linemate.setQuantity(resources[0]);
        tiles[y][x].deraumere.setQuantity(resources[1]);
        tiles[y][x].sibur.setQuantity(resources[2]);
        tiles[y][x].mendiane.setQuantity(resources[3]);
        tiles[y][x].phiras.setQuantity(resources[4]);
        tiles[y][x].thystame.setQuantity(resources[5]);
        updateDrawable();
    }
}

void Map::addPlayer(std::unique_ptr<Player> player)
{
    int playerNumber = player->getPlayerNumber();
    players[playerNumber] = std::move(player);
}

void Map::removePlayer(int playerNumber)
{
    players.erase(playerNumber);
}

Player* Map::getPlayer(int playerNumber)
{
    auto it = players.find(playerNumber);
    if (it != players.end())
        return it->second.get();
    return nullptr;
}

void Map::updateDrawable()
{
    mapDrawable.clear();
    mapDrawable.setPrimitiveType(sf::Quads);
    mapDrawable.resize(width * height * 4);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const Tile& tile = tiles[y][x];
            sf::Vertex* quad = &mapDrawable[(x + y * width) * 4];
            quad[0].position = sf::Vector2f(x * 32, y * 32);
            quad[1].position = sf::Vector2f((x + 1) * 32, y * 32);
            quad[2].position = sf::Vector2f((x + 1) * 32, (y + 1) * 32);
            quad[3].position = sf::Vector2f(x * 32, (y + 1) * 32);
            quad[0].color = sf::Color::White;
            quad[1].color = sf::Color::White;
            quad[2].color = sf::Color::White;
            quad[3].color = sf::Color::White;
        }
    }

}

sf::Drawable& Map::getDrawable()
{
    return mapDrawable;
}
