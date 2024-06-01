/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <unordered_map>
#include <queue>
#include <mutex>
#include "IResources.hpp"
#include "raylib.h"
#include "../Team/Team.hpp"
#include <memory>

namespace Zappy {
    enum class Orientation {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };

    class Player {
        public:
            Player(
                int playerNumber,
                std::unique_ptr<Team> team,
                Orientation orientation,
                int level
            );

            int getPlayerNumber() const;
            const Team* getTeam() const;
            Orientation getOrientation() const;
            int getLevel() const;

            void setOrientation(Orientation orientation);
            void setLevel(int level);

            void addResource(Zappy::Resources::Type type, int quantity);
            void setResource(Zappy::Resources::Type type, int quantity);
            void removeResource(Zappy::Resources::Type type, int quantity);
            int getResourceQuantity(const Zappy::Resources::IResources* resource) const;

            void setPosition(int x, int y);
            std::pair<int, int> getPosition() const;

            void addBroadcast(const std::string& message);
            std::string getBroadcast();

            void draw();

        protected:
        private:
            int playerNumber;
            std::unique_ptr<Team> _team;
            Orientation orientation;
            int level;
            std::unordered_map<Zappy::Resources::Type, int> inventory;
            std::queue<std::string> broadcast;
            std::mutex messageMutex;
            int x;
            int y;
    };

}

#endif /* !PLAYER_HPP_ */
