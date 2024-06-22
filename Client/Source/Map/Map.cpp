/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>
#include "Debug.hpp"
#include <random>
#include "Exceptions.hpp"

using namespace Zappy;

Map::Map()
{
    setSize(0, 0);
    _teams.clear();

    _camera = { 0 };
    _camera.position = { -5.0f, 5.0f, -5.0f };
    _camera.target = { 0.0f, 0.0f, 0.0f };
    _camera.up = { 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
}

void Map::loadModels()
{
    try {
        _resourcesModel.emplace(Resources::Type::FOOD, Model3D("Client/Models/Ingot/Ingot.obj", "Client/Models/Ingot/CopperIngot.png"));
        _resourcesModel.emplace(Resources::Type::LINEMATE, Model3D("Client/Models/Ingot/Ingot.obj", "Client/Models/Ingot/CopperIngot.png"));
        _resourcesModel.emplace(Resources::Type::DERAUMERE, Model3D("Client/Models/Ingot/Ingot.obj", "Client/Models/Ingot/GoldIngot.png"));
        _resourcesModel.emplace(Resources::Type::SIBUR, Model3D("Client/Models/Ingot/Ingot.obj", "Client/Models/Ingot/IronIngot.png"));
        _resourcesModel.emplace(Resources::Type::MENDIANE, Model3D("Client/Models/Ingot/Ingot.obj", "Client/Models/Ingot/MithrilIngot.png"));
        _resourcesModel.emplace(Resources::Type::PHIRAS, Model3D("Client/Models/Ingot/Ingot.obj", "Client/Models/Ingot/SilverIngot.png"));
        _resourcesModel.emplace(Resources::Type::THYSTAME, Model3D("Client/Models/Ingot/Ingot.obj", "Client/Models/Ingot/ThoriumIngot.png"));

        _eolienneModel = Model3D("Client/Models/Eolienne/EolicOBJ.obj");
    } catch (const std::exception &e) {
        throw ModelException("Failed to load models: " + std::string(e.what()));
    }
}

void Map::setSize(int width, int height)
{
    _width = width;
    _height = height;
    int tileSize = 32;
    _tiles.resize(height);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> freq_dist(0.05f, 0.2f);
    std::uniform_real_distribution<float> ampl_dist(0.5f, 2.0f);
    float frequency = freq_dist(gen);
    float amplitude = ampl_dist(gen);

    for (int y = 0; y < height; ++y) {
        _tiles[y].resize(width);
        for (int x = 0; x < width; ++x)
            _tiles[y][x] = Tile(x, y, tileSize, frequency, amplitude);
    }
    DEBUG_SUCCESS("Map size set to: " + std::to_string(width) + "x" + std::to_string(height));
}

void Map::updateTile(int x, int y, const std::vector<int>& resources)
{
    DEBUG_SUCCESS("Updating tile at: " + std::to_string(x) + ", " + std::to_string(y) + " with " +
    std::to_string(resources.size()) + " resource(s): " + std::to_string(resources[0]) +
    " - " + std::to_string(resources[1]) + " - " + std::to_string(resources[2]) +
    " - " + std::to_string(resources[3]) + " - " + std::to_string(resources[4]) +
    " - " + std::to_string(resources[5]) + " - " + std::to_string(resources[6]));
    if (x >= 0 && x < _width && y >= 0 && y < _height && resources.size() == 7)
        _tiles[y][x].setResources(resources);
}

std::vector<std::vector<Tile>> Map::getTiles() const
{
    return _tiles;
}

void Map::addPlayer(std::unique_ptr<Player> player)
{
    int playerNumber = player->getPlayerNumber();
    _players[playerNumber] = std::move(player);
    DEBUG_SUCCESS("Player added - ID: " + std::to_string(playerNumber) + " - Team: " + _players[playerNumber]->getTeam()->getName());
}

void Map::removePlayer(int playerNumber)
{
    _players.erase(playerNumber);
}

Player* Map::getPlayer(int playerNumber)
{
    auto it = _players.find(playerNumber);
    if (it != _players.end())
        return it->second.get();
    return nullptr;
}

void Map::draw(Camera camera)
{
    std::vector<Player*> players;
    for (const auto& [id, player] : _players)
        players.push_back(player.get());
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x)
            _tiles[y][x].draw(x, y, _resourcesModel, getPlayers(), _eolienneModel);
    }
    for (auto& player : _players) {
        float height = getTile(
            player.second->getPosition().first,
            player.second->getPosition().second
        )->getTileHeight();
        player.second->draw(camera, height);
    }
    for (auto& egg : _eggs) {
        float height = getTile(
            egg.second->getPosition().first,
            egg.second->getPosition().second
        )->getTileHeight();
        egg.second->draw(_egsModel, height);
    }
}

void Map::setTeams(const std::vector<std::string>& teams)
{
    Color colors[] = {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        ORANGE,
        PINK,
        PURPLE,
        BROWN
    };

    for (size_t i = 0; i < teams.size(); ++i)
        _teams[teams[i]] = std::make_unique<Team>(teams[i], colors[i]);
}

Color Map::generateUniqueColor()
{
    Color teamColor;
    bool isUnique;
    do {
        teamColor = {(unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), 255};
        isUnique = true;
        for (const auto& team : _teams) {
            Color color = team.second->getColor();
            if (color.r == teamColor.r && color.g == teamColor.g && color.b == teamColor.b) {
                isUnique = false;
                break;
            }
        }
    } while (
        !isUnique || teamColor.r == 0 || teamColor.g == 0 || teamColor.b == 0 ||
        teamColor.r == 255 || teamColor.g == 255 || teamColor.b == 255
    );
    return teamColor;
}

void Map::addTeam(std::string name) {
    std::lock_guard<std::mutex> lock(_teamMutex);
    Color teamColor = generateUniqueColor();
    _teams[name] = std::make_unique<Team>(name, teamColor);
    DEBUG_SUCCESS("Team added: " + name + " with color: " + std::to_string(teamColor.r) + ", " + std::to_string(teamColor.g) + ", " + std::to_string(teamColor.b));
}
Team* Map::getTeam(std::string name) const
{
    auto it = _teams.find(name);
    if (it != _teams.end())
        return it->second.get();
    return nullptr;
}

std::vector<Team*> Map::getTeams() const
{
    std::vector<Team*> teams;
    for (auto& team : _teams)
        teams.push_back(team.second.get());
    return teams;
}

Tile* Map::getTile(int x, int y)
{
    if (x >= 0 && x < _width && y >= 0 && y < _height)
        return &_tiles[y][x];
    return nullptr;
}

void Map::addServerMessage(const std::string& message)
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    _serverMessages.push({message, std::chrono::steady_clock::now()});
    DEBUG_SUCCESS("Server message added: " + message);
}

std::string Map::getServerMessage()
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    if (_serverMessages.empty())
        return "";

    auto& oldestMsg = _serverMessages.front();
    auto now = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - oldestMsg.timestamp).count();

    constexpr int minDisplayDuration = 10000;

    int displayDuration = minDisplayDuration + oldestMsg.message.size() * 100;

    if (elapsedTime < displayDuration)
        return oldestMsg.message;

    std::string message = oldestMsg.message;
    _serverMessages.pop();
    return message;
}

void Map::setTimeUnit(int timeUnit)
{
    _timeUnit = timeUnit;
    DEBUG_SUCCESS("Time unit set to: " + std::to_string(timeUnit));
}

int Map::getTimeUnit() const
{
    return _timeUnit;
}

void Map::addEgg(std::unique_ptr<Egg> egg)
{
    int eggNumber = egg->getEggNumber();
    _eggs[eggNumber] = std::move(egg);
    DEBUG_SUCCESS("Egg added - ID: " + std::to_string(eggNumber) + " - Pos: " +
    std::to_string(_eggs[eggNumber]->getPosition().first) + ", " +
    std::to_string(_eggs[eggNumber]->getPosition().second));
}

void Map::removeEgg(int eggNumber)
{
    _eggs.erase(eggNumber);
    DEBUG_SUCCESS("Egg removed - ID: " + std::to_string(eggNumber));
}

Egg* Map::getEgg(int eggNumber)
{
    auto it = _eggs.find(eggNumber);
    if (it != _eggs.end())
        return it->second.get();
    return nullptr;
}

int Map::getWidth() const
{
    return _width;
}

int Map::getHeight() const
{
    return _height;
}

void Map::setWiner(const std::string& winer)
{
    _winer = winer;
    _cameraMode = CameraMode::CAMERA_ORBITAL;
    Vector3 mapCenter = { (float)_width / 2, 0.0f, (float)_height / 2 };
    _camera.target = mapCenter;
    _camera.position = { 0, 8, 0 };
    DEBUG_SUCCESS("Winer set to: " + winer);
}

std::string Map::getWiner() const
{
    return _winer;
}

std::vector<Player*> Map::getPlayers() const
{
    std::vector<Player*> players;
    for (auto& player : _players)
        players.push_back(player.second.get());
    return players;
}

void Map::setCameraMode(CameraMode mode)
{
    _cameraMode = mode;
}

CameraMode Map::getCameraMode() const
{
    return _cameraMode;
}

Camera3D Map::getCamera() const
{
    return _camera;
}

Camera3D* Map::getCameraPtr()
{
    return &_camera;
}

std::vector<Egg*> Map::getEggs()
{
    std::vector<Egg*> eggs;
    for (auto& egg : _eggs)
        eggs.push_back(egg.second.get());
    return eggs;
}

std::vector<Player*> Map::getPlayersOnTile(int x, int y)
{
    std::vector<Player*> playersOnTile;
    for (auto& pair : _players) {
        Player* player = pair.second.get();
        auto [playerX, playerY] = player->getPosition();
        if (playerX == x && playerY == y)
            playersOnTile.push_back(player);
    }
    return playersOnTile;
}

void Map::update(float deltaTime)
{
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x)
            _tiles[y][x].update(deltaTime);
    }
    for (auto& player : _players)
        player.second->update(deltaTime);
    for (auto& egg : _eggs)
        egg.second->update(deltaTime);
}
