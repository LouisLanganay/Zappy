/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#include "Player.hpp"
#include <queue>
#include <mutex>
#include "Debug.hpp"

using namespace Zappy;

Player::Player(
    int playerNumber,
    std::unique_ptr<Team> team,
    Orientation orientation,
    int level
) : _playerNumber(playerNumber),
    _orientation(orientation),
    _team(std::move(team)),
    _level(level)
{
    _x = 0;
    _y = 0;

    _inventory[Zappy::Resources::Type::FOOD] = 0;
    _inventory[Zappy::Resources::Type::LINEMATE] = 0;
    _inventory[Zappy::Resources::Type::DERAUMERE] = 0;
    _inventory[Zappy::Resources::Type::SIBUR] = 0;
    _inventory[Zappy::Resources::Type::MENDIANE] = 0;
    _inventory[Zappy::Resources::Type::PHIRAS] = 0;
    _inventory[Zappy::Resources::Type::THYSTAME] = 0;

}

int Player::getPlayerNumber() const
{
    return _playerNumber;
}

const Team* Player::getTeam() const
{
    return _team.get();
}

Orientation Player::getOrientation() const
{
    return _orientation;
}

int Player::getLevel() const
{
    return _level;
}

void Player::setOrientation(Orientation orientation)
{
    _orientation = orientation;
}

void Player::setLevel(int level)
{
    _level = level;
}

void Player::addResource(Zappy::Resources::Type type, int quantity)
{
    _inventory[type] += quantity;
}

void Player::setResource(Zappy::Resources::Type type, int quantity)
{
    _inventory[type] = quantity;
}

void Player::removeResource(Zappy::Resources::Type type, int quantity)
{
    if (_inventory[type] >= quantity)
        _inventory[type] -= quantity;
    else
        _inventory[type] = 0;
}

int Player::getResourceQuantity(const Zappy::Resources::IResources* resource) const
{
    auto it = _inventory.find(resource->getType());
    if (it != _inventory.end())
        return it->second;
    return 0;
}

void Player::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

std::pair<int, int> Player::getPosition() const
{
    return {_x, _y};
}

void Player::addBroadcast(const std::string& message)
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    _broadcast.push(message);
    DEBUG_SUCCESS("Player " + std::to_string(_playerNumber) + " broadcasted: " + message);
}

std::string Player::getBroadcast()
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    if (_broadcast.empty())
        return "";
    std::string message = _broadcast.front();
    _broadcast.pop();
    return message;
}

void Player::draw(Camera camera)
{
    Vector3 position = {(float)_x, 0.5f, (float)_y};

    DrawCube(position, 0.5f, 0.5f, 0.5f, _team->getColor());
    DrawCubeWires(position, 0.5f, 0.5f, 0.5f, BLACK);

    Vector3 spherePosition = position;
    if (_orientation == Orientation::NORTH)
        spherePosition.z -= 0.2f;
    else if (_orientation == Orientation::SOUTH)
        spherePosition.z += 0.2f;
    else if (_orientation == Orientation::EAST)
        spherePosition.x += 0.2f;
    else if (_orientation == Orientation::WEST)
        spherePosition.x -= 0.2f;

    spherePosition.y += 0.2f;

    DrawSphere(spherePosition, 0.2f, BLACK);

    // TODO: Draw player level and broadcast messages
}

std::unordered_map<Zappy::Resources::Type, int> Player::getInventory() const
{
    return _inventory;
}

void Player::layEgg()
{
    DEBUG_SUCCESS("Player " + std::to_string(_playerNumber) + " laid an egg");
    // TODO: Implement laying egg animation
}
