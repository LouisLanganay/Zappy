/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Food
*/

#ifndef FOOD_HPP
#define FOOD_HPP

#include "AResources.hpp"

namespace Zappy::Resources
{
    class Food : public AResources {
        public:
            Food(int initialQuantity = 0);
            ~Food();

        protected:
        private:
    };
}


#endif // FOOD_HPP