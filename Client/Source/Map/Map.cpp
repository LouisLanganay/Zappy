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
    _teams.clear();
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
    DEBUG_INFO("Updating tile at: " + std::to_string(x) + ", " + std::to_string(y) + " with resources: " +
    std::to_string(resources.size()) + " - " + std::to_string(resources[0]) +
    " - " + std::to_string(resources[1]) + " - " + std::to_string(resources[2]) +
    " - " + std::to_string(resources[3]) + " - " + std::to_string(resources[4]) +
    " - " + std::to_string(resources[5]) + " - " + std::to_string(resources[6]) +
    " - " + std::to_string(resources[7]));
    if (x >= 0 && x < _width && y >= 0 && y < _height && resources.size() == 7)
        _tiles[y][x].setResources(resources);
}

void Map::addPlayer(std::unique_ptr<Player> player)
{
    int playerNumber = player->getPlayerNumber();
    _players[playerNumber] = std::move(player);
    DEBUG_SUCCESS("Player added - ID: " + std::to_string(playerNumber) + " - Team: " + _players[playerNumber]->getTeam()->getName());
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
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x)
            _tiles[y][x].draw(x, y);
    }
    for (auto& player : _players)
        player.second->draw();
}

void Map::setTeams(const std::vector<std::string>& teams)
{
    Color colors[] = {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        ORANGE,
        PINK,
        PURPLE,
        BROWN
    };

    for (size_t i = 0; i < teams.size(); ++i)
        _teams[teams[i]] = std::make_unique<Team>(teams[i], colors[i]);
}

void Map::addTeam(std::string name)
{
    Color colors[] = {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        ORANGE,
        PINK,
        PURPLE,
        BROWN
    };

    Color teamColor = colors[_teams.size() % 8];

    _teams[name] = std::make_unique<Team>(name, teamColor);
    DEBUG_SUCCESS("Team added: " + name + " with color: " + std::to_string(teamColor.r) + ", " + std::to_string(teamColor.g) + ", " + std::to_string(teamColor.b));
}

Team* Map::getTeam(std::string name) const
{
    auto it = _teams.find(name);
    if (it != _teams.end())
        return it->second.get();
    return nullptr;
}

Tile* Map::getTile(int x, int y)
{
    if (x >= 0 && x < _width && y >= 0 && y < _height)
        return &_tiles[y][x];
    return nullptr;
}

void Map::addServerMessage(const std::string& message)
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    _serverMessages.push(message);
}

std::string Map::getServerMessage()
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    if (_serverMessages.empty())
        return "";
    std::string message = _serverMessages.front();
    _serverMessages.pop();
    return message;
}
