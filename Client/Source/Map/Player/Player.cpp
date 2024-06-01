/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#include "Player.hpp"
#include <queue>
#include <mutex>

using namespace Zappy;

Player::Player(
    int playerNumber,
    const std::string& team,
    Orientation orientation,
    int level
) : playerNumber(playerNumber),
    team(team),
    orientation(orientation),
    level(level)
{
    x = 0;
    y = 0;

    inventory[Zappy::Resources::Type::FOOD] = 0;
    inventory[Zappy::Resources::Type::LINEMATE] = 0;
    inventory[Zappy::Resources::Type::DERAUMERE] = 0;
    inventory[Zappy::Resources::Type::SIBUR] = 0;
    inventory[Zappy::Resources::Type::MENDIANE] = 0;
    inventory[Zappy::Resources::Type::PHIRAS] = 0;
    inventory[Zappy::Resources::Type::THYSTAME] = 0;
}

int Player::getPlayerNumber() const
{
    return playerNumber;
}

std::string Player::getTeam() const
{
    return team;
}

Orientation Player::getOrientation() const
{
    return orientation;
}

int Player::getLevel() const
{
    return level;
}

void Player::setOrientation(Orientation orientation)
{
    this->orientation = orientation;
}

void Player::setLevel(int level)
{
    this->level = level;
}

void Player::addResource(Zappy::Resources::Type type, int quantity)
{
    inventory[type] += quantity;
}

void Player::setResource(Zappy::Resources::Type type, int quantity)
{
    inventory[type] = quantity;
}

void Player::removeResource(Zappy::Resources::Type type, int quantity)
{
    if (inventory[type] >= quantity)
        inventory[type] -= quantity;
    else
        inventory[type] = 0;
}

int Player::getResourceQuantity(const Zappy::Resources::IResources* resource) const
{
    auto it = inventory.find(resource->getType());
    if (it != inventory.end())
        return it->second;
    return 0;
}

void Player::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

std::pair<int, int> Player::getPosition() const
{
    return {x, y};
}

void Player::addBroadcast(const std::string& message)
{
    std::lock_guard<std::mutex> lock(messageMutex);
    broadcast.push(message);
}

std::string Player::getBroadcast()
{
    std::lock_guard<std::mutex> lock(messageMutex);
    if (broadcast.empty())
        return "";
    std::string message = broadcast.front();
    broadcast.pop();
    return message;
}

void Player::draw()
{
    Vector3 position = {(float)x, 0.5f, (float)y};

    // Draw smaller cube for the player
    DrawCube(position, 0.5f, 0.5f, 0.5f, RED);
    DrawCubeWires(position, 0.5f, 0.5f, 0.5f, BLACK);

    // Calculate position for sphere indicating orientation
    Vector3 spherePosition = position;
    if (orientation == Orientation::NORTH)
        spherePosition.z -= 0.2f;
    else if (orientation == Orientation::SOUTH)
        spherePosition.z += 0.2f;
    else if (orientation == Orientation::EAST)
        spherePosition.x += 0.2f;
    else if (orientation == Orientation::WEST)
        spherePosition.x -= 0.2f;

    spherePosition.y += 0.2f;

    // Draw sphere indicating orientation
    DrawSphere(spherePosition, 0.2f, GREEN);
}
