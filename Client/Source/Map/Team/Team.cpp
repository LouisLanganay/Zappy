/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Team
*/

#include "Team.hpp"

using namespace Zappy;

Team::Team(const std::string& name, const Color& color)
    : name(name), color(color)
{
}

std::string Team::getName() const
{
    return name;
}

Color Team::getColor() const
{
    return color;
}
