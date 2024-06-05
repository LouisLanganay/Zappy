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
#include <map>
#include <queue>
#include <mutex>
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
#include "Tile/Tile.hpp"
#include "Team/Team.hpp"
#include "Egg/Egg.hpp"

namespace Zappy {

    class Map {
        public:
            Map();
            void updateTile(int x, int y, const std::vector<int>& resources);
            void addPlayer(std::unique_ptr<Player> player);
            void removePlayer(int playerNumber);
            void draw(Camera camera);
            void setSize(int width, int height);

            Player* getPlayer(int playerNumber);

            void addTeam(std::string name);
            void setTeams(const std::vector<std::string>& teams);
            Team* getTeam(std::string name) const;


            Tile* getTile(int x, int y);

            void addServerMessage(const std::string& message);
            std::string getServerMessage();

            void setTimeUnit(int timeUnit);
            int getTimeUnit() const;

            void addEgg(std::unique_ptr<Egg> egg);
            void removeEgg(int eggNumber);
            Egg* getEgg(int eggNumber);
        private:
            std::vector<std::vector<Tile>> _tiles;
            std::unordered_map<std::string, std::unique_ptr<Team>> _teams;
            std::unordered_map<int, std::unique_ptr<Player>> _players;
            std::unordered_map<int, std::unique_ptr<Egg>> _eggs;
            std::queue<std::string> _serverMessages;
            std::mutex _messageMutex;
            int _height;
            int _width;
            int _timeUnit;
    };
};

#endif /* !MAP_HPP_ */
