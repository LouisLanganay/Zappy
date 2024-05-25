/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AResources
*/

#include "AResources.hpp"

using namespace Zappy::Resources;

AResources::AResources(
    const std::string &type,
    int initialQuantity
) : quantity(initialQuantity)
{
    if (type == "q0")
        this->type = Type::FOOD;
    else if (type == "q1")
        this->type = Type::LINEMATE;
    else if (type == "q2")
        this->type = Type::DERAUMERE;
    else if (type == "q3")
        this->type = Type::SIBUR;
    else if (type == "q4")
        this->type = Type::MENDIANE;
    else if (type == "q5")
        this->type = Type::PHIRAS;
    else if (type == "q6")
        this->type = Type::THYSTAME;
}

Type AResources::getType() const
{
    return type;
}

int AResources::getQuantity() const
{
    return quantity;
}

void AResources::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void AResources::addQuantity(int quantity)
{
    this->quantity += quantity;
}

void AResources::removeQuantity(int quantity)
{
    if (this->quantity >= quantity)
        this->quantity -= quantity;
}
