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
#include <cmath>
#include <random>

using namespace Zappy;

Tile::Tile(int x, int y, int size, float frequency, float amplitude)
    : _x(x), _y(y), _size(size)
{
    _resources[Zappy::Resources::Type::FOOD] = 0;
    _resources[Zappy::Resources::Type::LINEMATE] = 0;
    _resources[Zappy::Resources::Type::DERAUMERE] = 0;
    _resources[Zappy::Resources::Type::SIBUR] = 0;
    _resources[Zappy::Resources::Type::MENDIANE] = 0;
    _resources[Zappy::Resources::Type::PHIRAS] = 0;
    _resources[Zappy::Resources::Type::THYSTAME] = 0;

    _tileHeight = amplitude * sin(frequency * x) * cos(frequency * y);
}

Color Tile::interpolateColor(
    const Color& colorLowGreen,
    const Color& colorHighGreen,
    float height
) const
{
    float t = std::clamp(height, 0.0f, 1.0f);

    unsigned char r = static_cast<unsigned char>((1.0f - t) * colorLowGreen.r + t * colorHighGreen.r);
    unsigned char g = static_cast<unsigned char>((1.0f - t) * colorLowGreen.g + t * colorHighGreen.g);
    unsigned char b = static_cast<unsigned char>((1.0f - t) * colorLowGreen.b + t * colorHighGreen.b);
    unsigned char a = static_cast<unsigned char>((1.0f - t) * colorLowGreen.a + t * colorHighGreen.a);

    return { r, g, b, a };
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

void Tile::drawParticles(float x, float y, float z) const
{
    int numParticles = 20;
    for (int i = 0; i < numParticles; ++i) {
        float angle = (2 * M_PI / numParticles) * i;
        float radius = 0.4f;
        float particleX = x + radius * cos(angle);
        float particleZ = z + radius * sin(angle);
        DrawSphere((Vector3){particleX, y + 0.03f, particleZ}, 0.03f, (Color){255, 255, 255, 255});
    }
}

void Tile::draw(
    int x,
    int y,
    std::map<Zappy::Resources::Type, Model3D> resources,
    const std::vector<Zappy::Player*>& players
) const
{
    Color colorLowGreen = { 28, 159, 50, 255 };
    Color colorHighGreen = { 42, 203, 69, 255 };

    Color colorDirt = {136, 93, 42, 255};
    Color colorDirtWire = {159, 108, 47, 255};

    Color tileUpColor = interpolateColor(colorLowGreen, colorHighGreen, getTileHeight());
    Color tileUpWireColor = interpolateColor(colorHighGreen, colorLowGreen, getTileHeight());

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
            if (team)
                tileUpColor = team->getColor();
            drawParticles((float)x, getTileHeight(), (float)y);
        }
    }

    DrawCube((Vector3){ (float)x, getTileHeight(), (float)y }, 1.0f, 0.1f, 1.0f, tileUpColor);
    DrawCube((Vector3){ (float)x, getTileHeight() - 0.2f - 0.1f, (float)y }, 1.0f, 0.5f, 1.0f, colorDirt);

    DrawCubeWires((Vector3){ (float)x, getTileHeight(), (float)y }, 1.0f, 0.1f, 1.0f, tileUpWireColor);
    DrawCubeWires((Vector3){ (float)x, getTileHeight() - 0.2f - 0.1f, (float)y }, 1.0f, 0.5f, 1.0f, colorDirtWire);

    Vector3 positions[] = {
        {(float)x - 0.4f, getTileHeight() + 0.05f, (float)y - 0.3f}, // FOOD
        {(float)x + 0.4f, getTileHeight() + 0.05f, (float)y - 0.3f}, // LINEMATE
        {(float)x - 0.4f, getTileHeight() + 0.05f, (float)y + 0.3f}, // DERAUMERE
        {(float)x + 0.4f, getTileHeight() + 0.05f, (float)y + 0.3f}, // SIBUR
        {(float)x, getTileHeight() + 0.05f, (float)y},               // MENDIANE
        {(float)x - 0.4f, getTileHeight() + 0.05f, (float)y},        // PHIRAS
        {(float)x + 0.4f, getTileHeight() + 0.05f, (float)y}         // THYSTAME
    };

    for (int i = 0; i < 7; ++i) {
        auto resourceType = static_cast<Zappy::Resources::Type>(i);
        int resourceCount = _resources.at(resourceType);
        for (int j = 0; j < resourceCount; ++j) {
            float offset = 0.040f * j;
            if (resourceType == Resources::Type::FOOD) {
                DrawSphere(positions[i], 0.05, WHITE);
                continue;
            }
            auto model = resources.at(resourceType);
            model.setPosition(positions[i].x, positions[i].y + offset, positions[i].z);
            model.setSize(0.2);
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
    _animationTime = 0.0f;
}

void Tile::endIncantation(int result)
{
    _incantationInProgress = false;
}

const std::vector<int>& Tile::getIncantationPlayers() const
{
    return _incantationPlayers;
}

float Tile::getTileHeight() const
{
    float incantationHeightOffset = _incantationInProgress ? 0.1f * sin(_animationTime) : 0.0f;
    return _tileHeight + incantationHeightOffset;
}

void Tile::update(float deltaTime)
{
    _animationTime += deltaTime;
    if (_animationTime > 2 * M_PI)
        _animationTime -= 2 * M_PI;
}
