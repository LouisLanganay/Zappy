/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#include "Player.hpp"

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

void Player::addResource(Zappy::Resources::IResources* resource, int quantity)
{
    inventory[resource->getType()] += quantity;
}

void Player::removeResource(Zappy::Resources::IResources* resource, int quantity)
{
    if (inventory[resource->getType()] >= quantity)
        inventory[resource->getType()] -= quantity;
}

int Player::getResourceQuantity(const Zappy::Resources::IResources* resource) const
{
    auto it = inventory.find(resource->getType());
    if (it != inventory.end())
        return it->second;
    return 0;
}
