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
#include <chrono>
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
#include "../Model3D/Model3D.hpp"

namespace Zappy {
    struct ServerMessage {
        std::string message;
        std::chrono::time_point<std::chrono::steady_clock> timestamp;
    };
    class Map {
        public:
            Map();
            void updateTile(int x, int y, const std::vector<int>& resources);
            void draw(Camera camera);
            void setSize(int width, int height);

            void addPlayer(std::unique_ptr<Player> player);
            Player* getPlayer(int playerNumber);
            void removePlayer(int playerNumber);
            std::vector<Player*> getPlayers() const;

            void addTeam(std::string name);
            void setTeams(const std::vector<std::string>& teams);
            Team* getTeam(std::string name) const;
            std::vector<Team*> getTeams() const;


            Tile* getTile(int x, int y);
            std::vector<std::vector<Tile>> getTiles() const;

            void addServerMessage(const std::string& message);
            std::string getServerMessage();

            void setTimeUnit(int timeUnit);
            int getTimeUnit() const;

            void addEgg(std::unique_ptr<Egg> egg);
            void removeEgg(int eggNumber);
            Egg* getEgg(int eggNumber);
            std::vector<Egg*> getEggs();

            int getWidth() const;
            int getHeight() const;

            void setWiner(const std::string& winer);
            std::string getWiner() const;

            Color generateUniqueColor();

            void setCameraMode(CameraMode mode);
            CameraMode getCameraMode() const;

            Camera3D getCamera() const;
            Camera3D* getCameraPtr();

            std::vector<Player*> getPlayersOnTile(int x, int y);

            void loadModels();

        protected:
        private:
            std::unordered_map<int, std::unique_ptr<Player>> _players;
            std::vector<std::vector<Tile>> _tiles;
            std::unordered_map<std::string, std::unique_ptr<Team>> _teams;
            std::unordered_map<int, std::unique_ptr<Egg>> _eggs;
            Model3D _egsModel;
            std::queue<ServerMessage> _serverMessages;
            std::map<Resources::Type, Model3D> _resourcesModel;
            std::mutex _messageMutex;
            std::mutex _teamMutex;
            std::string _winer;
            int _height;
            int _width;
            int _timeUnit = 100;
            CameraMode _cameraMode = CameraMode::CAMERA_FREE;
            Camera3D _camera;
    };
};

#endif /* !MAP_HPP_ */
