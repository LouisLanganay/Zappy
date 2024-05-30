/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/


#ifndef TILE_HPP_
#define TILE_HPP_

#include <vector>
#include "raylib.h"
#include <string>

namespace Zappy {
    class Tile {
        public:
            Tile(int x = 0, int y = 0, int size = 32);
            void setResources(const std::vector<int>& resources);
            void draw() const;

        private:
            int _x;
            int _y;
            int _size;
            std::vector<int> _resources;
    };
};

#endif /* !TILE_HPP_ */
