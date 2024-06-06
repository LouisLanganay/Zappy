/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"
#include "Debug.hpp"

using namespace Zappy;

Egg::Egg(
    int eggNumber,
    int playerNumber,
    int x,
    int y,
    std::unique_ptr<Team> team
) : _eggNumber(eggNumber),
    _playerNumber(playerNumber),
    _position(x, y),
    _hatched(false),
    _team(std::move(team))
{
}

int Egg::getEggNumber() const
{
    return _eggNumber;
}

int Egg::getPlayerNumber() const
{
    return _playerNumber;
}

std::pair<int, int> Egg::getPosition() const
{
    return _position;
}

void Egg::setHatched(bool hatched)
{
    _hatched = hatched;
}

bool Egg::isHatched() const
{
    return _hatched;
}

void Egg::draw()
{
    Vector3 position = {(float)_position.first, 0.5f, (float)_position.second};
    DrawSphere(position, 0.35f, BROWN);
}

const Team* Egg::getTeam() const
{
    return _team.get();
}
