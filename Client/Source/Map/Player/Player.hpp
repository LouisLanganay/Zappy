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
#include "IResources.hpp"

namespace Zappy {
    enum class Orientation {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };

    class Player {
        public:
            Player(int playerNumber, const std::string& team, Orientation orientation, int level);

            int getPlayerNumber() const;
            std::string getTeam() const;
            Orientation getOrientation() const;
            int getLevel() const;

            void setOrientation(Orientation orientation);
            void setLevel(int level);

            void addResource(Zappy::Resources::IResources* resource, int quantity);
            void removeResource(Zappy::Resources::IResources* resource, int quantity);
            int getResourceQuantity(const Zappy::Resources::IResources* resource) const;

        protected:
        private:
            int playerNumber;
            std::string team;
            Orientation orientation;
            int level;
            std::unordered_map<Zappy::Resources::Type, int> inventory;
    };

}

#endif /* !PLAYER_HPP_ */
