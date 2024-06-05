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
) : eggNumber(eggNumber),
    playerNumber(playerNumber),
    position(x, y),
    hatched(false),
    _team(std::move(team))
{
}

int Egg::getEggNumber() const
{
    return eggNumber;
}

int Egg::getPlayerNumber() const
{
    return playerNumber;
}

std::pair<int, int> Egg::getPosition() const
{
    return position;
}

void Egg::setHatched(bool hatched)
{
    this->hatched = hatched;
}

bool Egg::isHatched() const
{
    return hatched;
}

void Egg::draw()
{
    Vector3 position = {(float)this->position.first, 0.5f, (float)this->position.second};
    DrawSphere(position, 0.35f, BROWN);
}

const Team* Egg::getTeam() const
{
    return _team.get();
}
