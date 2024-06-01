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
    std::unique_ptr<Team> team,
    Orientation orientation,
    int level
) : playerNumber(playerNumber),
    orientation(orientation),
    _team(std::move(team)),
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

const Team* Player::getTeam() const
{
    return _team.get();
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

    DrawCube(position, 0.5f, 0.5f, 0.5f, _team->getColor());
    DrawCubeWires(position, 0.5f, 0.5f, 0.5f, BLACK);

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

    DrawSphere(spherePosition, 0.2f, BLACK);
}
