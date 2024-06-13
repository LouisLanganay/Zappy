/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#include "Tile.hpp"
#include "Debug.hpp"
#include "../../../Exceptions.hpp"
#include <unordered_map>

using namespace Zappy;

Tile::Tile(int x, int y, int size)
    : _x(x), _y(y), _size(size)
{
    _resources[Zappy::Resources::Type::FOOD] = 0;
    _resources[Zappy::Resources::Type::LINEMATE] = 0;
    _resources[Zappy::Resources::Type::DERAUMERE] = 0;
    _resources[Zappy::Resources::Type::SIBUR] = 0;
    _resources[Zappy::Resources::Type::MENDIANE] = 0;
    _resources[Zappy::Resources::Type::PHIRAS] = 0;
    _resources[Zappy::Resources::Type::THYSTAME] = 0;
}

void Tile::setResources(const std::vector<int>& resources)
{
    _resources[Zappy::Resources::Type::FOOD] = resources[0];
    _resources[Zappy::Resources::Type::LINEMATE] = resources[1];
    _resources[Zappy::Resources::Type::DERAUMERE] = resources[2];
    _resources[Zappy::Resources::Type::SIBUR] = resources[3];
    _resources[Zappy::Resources::Type::MENDIANE] = resources[4];
    _resources[Zappy::Resources::Type::PHIRAS] = resources[5];
    _resources[Zappy::Resources::Type::THYSTAME] = resources[6];
}

void Tile::draw(
    int x,
    int y,
    std::map<Zappy::Resources::Type, Model3D> resources,
    const std::vector<Zappy::Player*>& players
) const
{
    Color tileColor = LIGHTGRAY;

    if (_incantationInProgress && !_incantationPlayers.empty()) {
        int playerId = _incantationPlayers.front();

        Zappy::Player* player = nullptr;
        for (const auto& p : players) {
            if (p->getPlayerNumber() == playerId) {
                player = p;
                break;
            }
        }

        if (player) {
            auto team = player->getTeam();
            if (team) {
                tileColor = team->getColor();
            }
        }
    }

    DrawCube((Vector3){ (float)x, 0.0f, (float)y }, 1.0f, 0.1f, 1.0f, tileColor);
    DrawCubeWires((Vector3){ (float)x, 0.0f, (float)y }, 1.0f, 0.1f, 1.0f, GRAY);

    Vector3 positions[] = {
        {(float)x - 0.4f, 0.05f, (float)y - 0.3f}, // FOOD
        {(float)x + 0.4f, 0.05f, (float)y - 0.3f}, // LINEMATE
        {(float)x - 0.4f, 0.05f, (float)y + 0.3f}, // DERAUMERE
        {(float)x + 0.4f, 0.05f, (float)y + 0.3f}, // SIBUR
        {(float)x, 0.05f, (float)y},               // MENDIANE
        {(float)x - 0.4f, 0.05f, (float)y},        // PHIRAS
        {(float)x + 0.4f, 0.05f, (float)y}         // THYSTAME
    };

    for (int i = 0; i < 7; ++i) {
        auto resourceType = static_cast<Zappy::Resources::Type>(i);
        int resourceCount = _resources.at(resourceType);
        for (int j = 0; j < resourceCount; ++j) {
            float offset = 0.05f * j;
            if (resourceType == Resources::Type::FOOD) {
                DrawSphere(positions[i], 0.08, WHITE);
                continue;
            }
            auto model = resources.at(resourceType);
            model.setPosition(positions[i].x, positions[i].y + offset, positions[i].z);
            model.setSize(0.3);
            model.draw();
        }
    }
}

void Tile::addResource(Zappy::Resources::Type type, int quantity)
{
    _resources[type] += quantity;
}

void Tile::removeResource(Zappy::Resources::Type type, int quantity)
{
    _resources[type] -= quantity;
    if (_resources[type] < 0)
        _resources[type] = 0;
}

std::unordered_map<Zappy::Resources::Type, int> Tile::getResources() const
{
    return _resources;
}

void Tile::startIncantation(int level, const std::vector<int>& players)
{
    _incantationLevel = level;
    _incantationPlayers = players;
    _incantationInProgress = true;
}

void Tile::endIncantation(int result)
{
    _incantationInProgress = false;
}

const std::vector<int>& Tile::getIncantationPlayers() const
{
    return _incantationPlayers;
}
