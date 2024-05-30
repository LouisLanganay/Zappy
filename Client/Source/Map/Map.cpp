/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>
#include "Debug.hpp"

using namespace Zappy;

Map::Map()
{
    setSize(0, 0);
}

void Map::setSize(int width, int height)
{
    _width = width;
    _height = height;
    int tileSize = 32;
    _tiles.resize(height);

    for (int y = 0; y < height; ++y) {
        _tiles[y].resize(width);
        for (int x = 0; x < width; ++x)
            _tiles[y][x] = Tile(x, y, tileSize);
    }
    DEBUG_SUCCESS("Map size set to: " + std::to_string(width) + "x" + std::to_string(height));
}

void Map::updateTile(int x, int y, const std::vector<int>& resources)
{
    if (x >= 0 && x < _width && y >= 0 && y < _height && resources.size() == 6) {
        _tiles[y][x].setResources(resources);
    }
}

void Map::addPlayer(std::unique_ptr<Player> player)
{
    int playerNumber = player->getPlayerNumber();
    _players[playerNumber] = std::move(player);
}

void Map::removePlayer(int playerNumber)
{
    _players.erase(playerNumber);
}

Player* Map::getPlayer(int playerNumber)
{
    auto it = _players.find(playerNumber);
    if (it != _players.end())
        return it->second.get();
    return nullptr;
}

void Map::draw()
{
    for (const auto& row : _tiles)
        for (const auto& tile : row)
            tile.draw();
}
