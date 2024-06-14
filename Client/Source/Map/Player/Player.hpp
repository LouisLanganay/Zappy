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
#include "../Egg/Egg.hpp"

namespace Zappy {
    enum class Orientation {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };

    struct PlayerBroadcast {
        std::string message;
        std::chrono::time_point<std::chrono::steady_clock> timestamp;
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
            std::unordered_map<Zappy::Resources::Type, int> getInventory() const;

            void setPosition(int x, int y);
            std::pair<int, int> getPosition() const;

            void addBroadcast(const std::string& message);
            std::string getBroadcast();

            void draw(Camera camera);

            void layEgg();

            void setSelected(bool isSelected);
            bool isSelected() const;

            void update(float deltaTime);

            void startIncantation();
            void endIncantation(int result);

            void generateRandomDrawPosition();

        protected:
        private:
            int _playerNumber;
            std::unique_ptr<Team> _team;
            Orientation _orientation;
            int _level;
            std::unordered_map<Zappy::Resources::Type, int> _inventory;
            std::unordered_map<int, std::unique_ptr<Egg>> _eggs;
            std::queue<PlayerBroadcast> _broadcasts;
            std::chrono::time_point<std::chrono::steady_clock> _lastBroadcastTime;
            std::mutex _messageMutex;
            float _x;
            float _y;
            float _targetX;
            float _targetY;
            bool _isMoving;
            bool _isSelected = false;
            Vector2 _drawPosition;
            float _movementSpeed; // Speed of movement per second
            float _timeAccumulator; // Time accumulator for interpolation

    };

}

#endif /* !PLAYER_HPP_ */
