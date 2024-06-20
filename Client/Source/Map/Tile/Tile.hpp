/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tile
*/


#ifndef TILE_HPP_
#define TILE_HPP_

#include "../Resources/AResources.hpp"
#include "../Resources/IResources.hpp"
#include "raylib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <map>
#include <memory>
#include "../Model3D/Model3D.hpp"
#include "../../Player/Player.hpp"

namespace Zappy {
    class Tile {
        public:
            Tile(int x = 0, int y = 0, int size = 32, float frequency = 0.1f, float amplitude = 1.0f);
            void setResources(const std::vector<int>& resources);
            void draw(
                int x,
                int y,
                std::map<Zappy::Resources::Type, Model3D> resources,
                const std::vector<Zappy::Player*>& players,
                Model3D eolienne
            ) const;

            void addResource(Zappy::Resources::Type type, int quantity);
            void removeResource(Zappy::Resources::Type type, int quantity);
            std::unordered_map<Zappy::Resources::Type, int> getResources() const;

            void startIncantation(int level, const std::vector<int>& players);
            void endIncantation(int result);
            const std::vector<int>& getIncantationPlayers() const;

            float getTileHeight() const;

            void drawParticles(float x, float y, float z) const;

            void update(float deltaTime);

        private:
            std::unordered_map<Zappy::Resources::Type, int> _resources;
            int _x;
            int _y;
            int _size;

            std::vector<int> _incantationPlayers;
            int _incantationLevel;
            bool _incantationInProgress = false;
            float _tileHeight = 0.00f;

            float _animationTime = 0.0f;

            Color interpolateColor(
                const Color& colorLow,
                const Color& colorHigh,
                float height
            ) const;

            bool _incantationSuccess = false;
    };
};

#endif /* !TILE_HPP_ */
