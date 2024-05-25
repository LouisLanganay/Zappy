/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "IResources.hpp"
#include "Player/Player.hpp"
#include "Resources/IResources.hpp"
#include "Resources/Linemate/Linemate.hpp"
#include "Resources/Deraumere/Deraumere.hpp"
#include "Resources/Sibur/Sibur.hpp"
#include "Resources/Mendiane/Mendiane.hpp"
#include "Resources/Phiras/Phiras.hpp"
#include "Resources/Thystame/Thystame.hpp"
#include "Resources/Food/Food.hpp"

namespace Zappy {
    class Map {
        public:
            Map();
            ~Map();
            void setSize(int width, int height);
            void updateTile(int x, int y, const std::vector<int>& resources);
            void addPlayer(std::unique_ptr<Player> player);
            void removePlayer(int playerNumber);
            Player* getPlayer(int playerNumber);
            sf::Drawable& getDrawable();

        private:
            int width;
            int height;
            struct Tile {
                Resources::Linemate linemate;
                Resources::Deraumere deraumere;
                Resources::Sibur sibur;
                Resources::Mendiane mendiane;
                Resources::Phiras phiras;
                Resources::Thystame thystame;
                Resources::Food food;
            };
            std::vector<std::vector<Tile>> tiles;
            std::unordered_map<int, std::unique_ptr<Player>> players;
            sf::VertexArray mapDrawable;
            void updateDrawable();
        };
};

#endif /* !MAP_HPP_ */
