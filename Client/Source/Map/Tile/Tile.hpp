/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/


#ifndef TILE_HPP_
#define TILE_HPP_

#include "../Resources/IResources.hpp"
#include "raylib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>

namespace Zappy {
    class Tile {
        public:
            Tile(int x = 0, int y = 0, int size = 32);
            void setResources(const std::vector<int>& resources);
            void draw(int x, int y) const;

            void addResource(Zappy::Resources::Type type, int quantity);
            void removeResource(Zappy::Resources::Type type, int quantity);

        private:
            std::unordered_map<Zappy::Resources::Type, int> _resources;
            int _x;
            int _y;
            int _size;
    };
};

#endif /* !TILE_HPP_ */
