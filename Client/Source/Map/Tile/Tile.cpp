/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#include "Tile.hpp"
#include "Debug.hpp"

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

void Tile::draw(int x, int y) const
{
    DrawCube((Vector3){ (float)x, 0.0f, (float)y }, 1.0f, 0.1f, 1.0f, LIGHTGRAY);
    DrawCubeWires((Vector3){ (float)x, 0.0f, (float)y }, 1.0f, 0.1f, 1.0f, GRAY);

    Vector3 positions[] = {
        {(float)x - 0.4f, 0.1f, (float)y - 0.4f}, // FOOD
        {(float)x + 0.4f, 0.1f, (float)y - 0.4f}, // LINEMATE
        {(float)x - 0.4f, 0.1f, (float)y + 0.4f}, // DERAUMERE
        {(float)x + 0.4f, 0.1f, (float)y + 0.4f}, // SIBUR
        {(float)x, 0.1f, (float)y},               // MENDIANE
        {(float)x - 0.4f, 0.1f, (float)y},        // PHIRAS
        {(float)x + 0.4f, 0.1f, (float)y}         // THYSTAME
    };

    Color colors[] = {
        RED,    // FOOD
        GREEN,  // LINEMATE
        BLUE,   // DERAUMERE
        PURPLE, // SIBUR
        ORANGE, // MENDIANE
        YELLOW, // PHIRAS
        PINK    // THYSTAME
    };

    for (int i = 0; i < 7; ++i) {
        int resourceCount = _resources.at(static_cast<Zappy::Resources::Type>(i));
        for (int j = 0; j < resourceCount; ++j) {
            float offset = 0.10f * j;
            DrawSphere((Vector3){ positions[i].x, positions[i].y + offset, positions[i].z }, 0.10f, colors[i]);
            DrawSphereWires((Vector3){ positions[i].x, positions[i].y + offset, positions[i].z }, 0.10f, 16, 16, BLACK);
        }
    }

    for (int i = 0; i < 7; i++) {
        int resourceCount = _resources.at(static_cast<Zappy::Resources::Type>(i));
        if (resourceCount > 0) {
            DrawText(std::to_string(resourceCount).c_str(), (int)(positions[i].x * 32), (int)(positions[i].z * 32), 10, BLACK);
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
