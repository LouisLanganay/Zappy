/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/

#include "Tile.hpp"

using namespace Zappy;

Tile::Tile(int x, int y, int size)
    : _x(x), _y(y), _size(size)
{
}

void Tile::setResources(const std::vector<int>& resources)
{
    _resources = resources;
}

void Tile::draw() const {
    DrawRectangle(_x * _size, _y * _size, _size, _size, GRAY);

    if (!_resources.empty()) {
        std::string resourceText = std::to_string(_resources[0]);
        DrawText(resourceText.c_str(), _x * _size + 5, _y * _size + 5, 10, BLACK);
    }
}
