/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Core.hpp"
#include "Debug.hpp"
#include "raylib.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <iostream>
#include "../Exceptions.hpp"
#include "../Particle/ParticleSystem.hpp"
#include "../Model3D/Model3D.hpp"


using namespace Zappy;

Core::Core(
    const std::string& host,
    int port
) : _api(std::make_unique<Api>(host, port)),
    _map(std::make_unique<Map>()),
    _particleSystem(std::make_unique<ParticleSystem>()),
    _running(true),
    _hudLeft(HudLeft()),
    _hudRight(HudRight())
{
    _networkThread = std::thread(&Core::handleServerMessages, this);
    DEBUG_INFO("Core created with host: " + host + " and port: " + std::to_string(port));
}

Core::~Core()
{
    stop();
    if (_networkThread.joinable())
        _networkThread.join();
}

void Core::stop()
{
    DEBUG_INFO("Core stopping");
    _running = false;
    _api->stop();
    if (_networkThread.joinable())
        _networkThread.join();
}


void Core::run() {
    try {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        DEBUG_INFO("Core is running");
        SetTraceLogLevel(LOG_NONE);
        InitWindow(screenWidth, screenHeight, "Zappy Game");
        DEBUG_INFO("Window initialized with size: " + std::to_string(screenWidth) + "x" + std::to_string(screenHeight));
        SetTargetFPS(60);
        DisableCursor();

        _hudRight.setHudPos({
            GetScreenWidth() - _hudRight.getHudWidth() - 20,
            GetScreenHeight() - _hudRight.getHudHeight()
        });

        _map->loadModels();

        while (!WindowShouldClose() && _running) {
            if (IsKeyPressed(KEY_I))
                adjustTimeUnit(1);
            if (IsKeyPressed(KEY_U))
                adjustTimeUnit(-1);

            for (auto &player : _map->getPlayers())
                player->update(GetFrameTime());
            for (auto &egg : _map->getEggs())
                egg->update(GetFrameTime());
            _particleSystem->update(GetFrameTime());
            UpdateCamera(_map->getCameraPtr(), _map->getCameraMode());
            BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(_map->getCamera());
            _map->draw(_map->getCamera());
            _particleSystem->draw();
            EndMode3D();
            _hudLeft.draw(_map.get());
            _hudRight.draw(_map.get());
            if (_map->getWiner() != "") {
                int screenWidth = GetScreenWidth();
                int screenHeight = GetScreenHeight();
                int rectWidth = GetScreenWidth();
                int rectHeight = GetScreenHeight();
                int rectX = (screenWidth - rectWidth) / 2;
                int rectY = (screenHeight - rectHeight) / 2;

                DrawRectangle(rectX, rectY, rectWidth, rectHeight, Fade(GRAY, 0.8f));

                std::string winnerText1 = "End of the game";
                std::string winnerText2 = "Winner: " + _map->getWiner();
                std::string winnerText3 = "Press ESC to quit";
                int textWidth1 = MeasureText(winnerText1.c_str(), 100);
                int textWidth2 = MeasureText(winnerText2.c_str(), 90);
                int textWidth3 = MeasureText(winnerText3.c_str(), 40);

                DrawText(winnerText1.c_str(), (screenWidth - textWidth1) / 2, screenHeight / 2 - 200, 100, RAYWHITE);
                DrawText(winnerText2.c_str(), (screenWidth - textWidth2) / 2, screenHeight / 2 - 50, 85, _map->getTeam(_map->getWiner())->getColor());
                DrawText(winnerText3.c_str(), (screenWidth - textWidth3) / 2, screenHeight / 2 + 100, 40, RAYWHITE);
            }
            EndDrawing();
        }
        CloseWindow();
        stop();
    } catch (const std::exception &e) {
        throw MainException(e.what());
    }
    DEBUG_ERROR("Core stopped");
}

void Core::handleServerMessages() {
    try {
        while (_running && _api->isRunning()) {
            std::string message = _api->getData();
            if (message.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
            DEBUG_INFO("Core received packet: " + message);
            if (message.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            if (message.find("WELCOME") == 0) {
                _api->sendCommand("GRAPHIC");
                if (_map->getWidth() == 0 && _map->getHeight() == 0) {
                    _api->requestMapSize();
                    _api->requestAllTilesContent();
                }
                if (_map->getTeams().empty()) {
                    _api->requestTeamsNames();
                }
                continue;
            }
            if (message.find("msz") == 0) {
                msz(message);
                continue;
            }
            if (message.find("bct") == 0) {
                bct(message);
                continue;
            }
            if (message.find("tna") == 0) {
                tna(message);
                continue;
            }
            if (message.find("pnw") == 0) {
                pnw(message);
                continue;
            }
            if (message.find("ppo") == 0) {
                ppo(message);
                continue;
            }
            if (message.find("plv") == 0) {
                plv(message);
                continue;
            }
            if (message.find("pin") == 0) {
                pin(message);
                continue;
            }
            if (message.find("pex") == 0) {
                pex(message);
                continue;
            }
            if (message.find("pbc") == 0) {
                pbc(message);
                continue;
            }
            if (message.find("pic") == 0) {
                pic(message);
                continue;
            }
            if (message.find("pie") == 0) {
                pie(message);
                continue;
            }
            if (message.find("pfk") == 0) {
                pfk(message);
                continue;
            }
            if (message.find("pdr") == 0) {
                pdr(message);
                continue;
            }
            if (message.find("pgt") == 0) {
                pgt(message);
                continue;
            }
            if (message.find("pdi") == 0) {
                pdi(message);
                continue;
            }
            if (message.find("enw") == 0) {
                enw(message);
                continue;
            }
            if (message.find("ebo") == 0) {
                ebo(message);
                continue;
            }
            if (message.find("edi") == 0) {
                edi(message);
                continue;
            }
            if (message.find("sgt") == 0) {
                sgt(message);
                continue;
            }
            if (message.find("sst") == 0) {
                sst(message);
                continue;
            }
            if (message.find("seg") == 0) {
                seg(message);
                continue;
            }
            if (message.find("smg") == 0) {
                smg(message);
                continue;
            }
            if (message.find("suc") == 0) {
                suc();
                continue;
            }
            if (message.find("sbp") == 0) {
                sbp();
                continue;
            }

            DEBUG_ERROR("Unknown command: " + message);
        }
    } catch (const std::exception& e) {
        throw MainException(e.what());
    }
}

void Core::adjustTimeUnit(int value)
{
    int timeUnit = _map->getTimeUnit();
    timeUnit += value;
    if (timeUnit < 1)
        timeUnit = 1;
    _map->setTimeUnit(timeUnit);
    _api->modifyTimeUnit(timeUnit);
}

void Core::msz(std::string message)
{
    int x, y;
    sscanf(message.c_str(), "msz %d %d", &x, &y);
    _map->setSize(x, y);
}

void Core::bct(std::string message) {
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    sscanf(message.c_str(), "bct %d %d %d %d %d %d %d %d %d", &x, &y, &q0, &q1, &q2, &q3, &q4, &q5, &q6);
    _map->updateTile(x, y, {q0, q1, q2, q3, q4, q5, q6});
}

void Core::tna(std::string message)
{
    std::string teamName = message.substr(4);

    teamName.erase(0, teamName.find_first_not_of(" \t\n\r"));
    teamName.erase(teamName.find_last_not_of(" \t\n\r") + 1);

    _map->addTeam(teamName);
}

void Core::pnw(std::string message)
{
    std::istringstream iss(message);
    std::string command;
    int playerNumber, x, y, orientation, level;
    std::string teamName;

    iss >> command;

    if (!(iss >> playerNumber >> x >> y >> orientation >> level >> teamName)) {
        DEBUG_ERROR("Malformed pnw message: " + message);
        return;
    }
    if (orientation < 1 || orientation > 4) {
        DEBUG_ERROR("Invalid orientation value: " + std::to_string(orientation));
        return;
    }

    Orientation orient = static_cast<Orientation>(orientation);
    const Team* team = _map->getTeam(teamName);
    if (!team) {
        DEBUG_ERROR("Team not found: " + teamName);
        return;
    }

    std::unique_ptr<Player> player = std::make_unique<Player>(
        playerNumber,
        std::make_unique<Team>(*team),
        orient,
        level
    );
    player->setPosition(x, y);
    _map->addPlayer(std::move(player));
}

void Core::ppo(std::string message)
{
    std::istringstream iss(message);
    std::string command;
    int playerNumber, x, y, orientation;

    iss >> command;

    if (!(iss >> playerNumber >> x >> y >> orientation)) {
        DEBUG_ERROR("Malformed ppo message: " + message);
        return;
    }
    if (orientation < 1 || orientation > 4) {
        DEBUG_ERROR("Invalid orientation value: " + std::to_string(orientation));
        return;
    }

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }

    player->setPosition(x, y);
    player->setOrientation(static_cast<Orientation>(orientation));
}

void Core::plv(std::string message)
{
    int playerNumber, level;
    sscanf(message.c_str(), "plv %d %d", &playerNumber, &level);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }

    player->setLevel(level);
}

void Core::pin(std::string message)
{
    int playerNumber, x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;
    sscanf(message.c_str(), "pin %d %d %d %d %d %d %d %d %d %d %d", &playerNumber, &x, &y, &food, &linemate, &deraumere, &sibur, &mendiane, &phiras, &thystame);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    player->setResource(Zappy::Resources::Type::FOOD, food);
    player->setResource(Zappy::Resources::Type::LINEMATE, linemate);
    player->setResource(Zappy::Resources::Type::DERAUMERE, deraumere);
    player->setResource(Zappy::Resources::Type::SIBUR, sibur);
    player->setResource(Zappy::Resources::Type::MENDIANE, mendiane);
    player->setResource(Zappy::Resources::Type::PHIRAS, phiras);
    player->setResource(Zappy::Resources::Type::THYSTAME, thystame);
    DEBUG_SUCCESS("Player " + std::to_string(playerNumber) + " inventory updated {" +
    std::to_string(food) + ", " + std::to_string(linemate) + ", " +
    std::to_string(deraumere) + ", " + std::to_string(sibur) + ", " +
    std::to_string(mendiane) + ", " + std::to_string(phiras) + ", " +
    std::to_string(thystame) + "}");
}

void Core::pex(std::string message)
{
    int playerNumber;
    sscanf(message.c_str(), "pex %d", &playerNumber);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    _api->requestPlayerPosition(playerNumber);

    auto [expellingPlayerX, expellingPlayerY] = player->getPosition();
    Zappy::Orientation orientation = player->getOrientation();

    _particleSystem->emit(ParticleType::EXPULSION, expellingPlayerX, 1, expellingPlayerY, 15);

    int dx = 0, dy = 0;
    switch (orientation) {
        case Zappy::Orientation::NORTH: dy = -1; break;
        case Zappy::Orientation::EAST:  dx = 1;  break;
        case Zappy::Orientation::SOUTH: dy = 1;  break;
        case Zappy::Orientation::WEST:  dx = -1; break;
    }

    for (Player* otherPlayer : _map->getPlayersOnTile(expellingPlayerX, expellingPlayerY)) {
        if (otherPlayer->getPlayerNumber() != playerNumber) {
            float targetX = otherPlayer->getPosition().first + dx;
            float targetY = otherPlayer->getPosition().second + dy;
            otherPlayer->setPosition(targetX, targetY);
        }
    }
}

void Core::pbc(std::string message)
{
    std::istringstream iss(message);
    std::string command;
    int playerNumber;
    std::string msg;
    iss >> command >> playerNumber;
    std::getline(iss, msg);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    player->addBroadcast(msg);
}

void Core::pic(std::string message)
{
    std::istringstream iss(message);
    std::string command;
    int x, y, level, playerNumber;
    iss >> command >> x >> y >> level;
    std::vector<int> players;
    while (iss >> playerNumber)
        players.push_back(playerNumber);

    Tile* tile = _map->getTile(x, y);
    if (!tile) {
        DEBUG_ERROR("Tile not found at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
        return;
    }

    _particleSystem->emit(ParticleType::INCANTATION, x, 1, y, 15);

    tile->startIncantation(level, players);
//
    //for (int playerId : players) {
    //    Player* player = _map->getPlayer(playerId);
    //    if (player)
    //        player->startIncantation();
    //    else
    //        DEBUG_ERROR("Player not found: " + std::to_string(playerId));
    //}
    DEBUG_INFO("Incantation started at (" + std::to_string(x) + ", " + std::to_string(y) + ") with level " + std::to_string(level) + " and players: " + std::to_string(players.size()));
}

void Core::pie(std::string message)
{
    int x, y, result;
    sscanf(message.c_str(), "pie %d %d %d", &x, &y, &result);

    Tile* tile = _map->getTile(x, y);
    if (!tile) {
        DEBUG_ERROR("Tile not found at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
        return;
    }

    _particleSystem->emit(ParticleType::INCANTATION, x, 1, y, 15);

    tile->endIncantation(result);
//
    //const std::vector<int>& players = tile->getIncantationPlayers();
    //for (int playerId : players) {
    //    Player* player = _map->getPlayer(playerId);
    //    if (player)
    //        player->endIncantation(result);
    //    else
    //        DEBUG_ERROR("Player not found: " + std::to_string(playerId));
    //}
    _api->requestTileContent(x, y);
    DEBUG_INFO("Incantation ended at (" + std::to_string(x) + ", " + std::to_string(y) + ") with result: " + std::to_string(result));
}


void Core::pfk(std::string message)
{
    int playerNumber;
    sscanf(message.c_str(), "pfk %d", &playerNumber);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    player->layEgg();
}

void Core::pdr(std::string message)
{
    int playerNumber, resource;
    sscanf(message.c_str(), "pdr %d %d", &playerNumber, &resource);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    player->removeResource(static_cast<Zappy::Resources::Type>(resource), 1);
    std::pair<int, int> pos = player->getPosition();
    Tile* tile = _map->getTile(pos.first, pos.second);
    if (!tile) {
        DEBUG_ERROR("Tile not found at " + std::to_string(pos.first) + " " + std::to_string(pos.second));
        return;
    }
    tile->addResource(static_cast<Zappy::Resources::Type>(resource), 1);
    _api->requestPlayerInventory(playerNumber);
    _api->requestTileContent(pos.first, pos.second);
}

void Core::pgt(std::string message)
{
    int playerNumber, resource;
    sscanf(message.c_str(), "pgt %d %d", &playerNumber, &resource);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    player->addResource(static_cast<Zappy::Resources::Type>(resource), 1);
    std::pair<int, int> pos = player->getPosition();
    Tile* tile = _map->getTile(pos.first, pos.second);
    if (!tile) {
        DEBUG_ERROR("Tile not found at " + std::to_string(pos.first) + " " + std::to_string(pos.second));
        return;
    }
    tile->removeResource(static_cast<Zappy::Resources::Type>(resource), 1);
    _api->requestPlayerInventory(playerNumber);
    _api->requestTileContent(pos.first, pos.second);
}

void Core::pdi(std::string message)
{
    int playerNumber;
    sscanf(message.c_str(), "pdi %d", &playerNumber);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    std::pair<int, int> pos = player->getPosition();
    Tile* tile = _map->getTile(pos.first, pos.second);
    if (!tile) {
        DEBUG_ERROR("Tile not found at " + std::to_string(pos.first) + " " + std::to_string(pos.second));
        return;
    }
    _map->removePlayer(playerNumber);
}

void Core::enw(std::string message)
{
    int eggNumber, playerNumber, x, y;
    sscanf(message.c_str(), "enw %d %d %d %d", &eggNumber, &playerNumber, &x, &y);

    Player* player = _map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    const Team* team = player->getTeam();
    if (!team) {
        DEBUG_ERROR("Team not found for player: " + std::to_string(playerNumber));
        return;
    }

    player->layEgg();

    _map->addEgg(std::make_unique<Egg>(
        eggNumber,
        playerNumber,
        x, y,
        std::make_unique<Team>(*team)
    ));
}

void Core::ebo(std::string message)
{
    int eggNumber;
    sscanf(message.c_str(), "ebo %d", &eggNumber);

    Egg* egg = _map->getEgg(eggNumber);
    if (!egg) {
        DEBUG_ERROR("Egg not found: " + std::to_string(eggNumber));
        return;
    }
    egg->startHatchingAnimation();
}

void Core::edi(std::string message)
{
    int eggNumber;
    sscanf(message.c_str(), "edi %d", &eggNumber);

    _map->removeEgg(eggNumber);
}

void Core::sgt(std::string message)
{
    int frequency;
    sscanf(message.c_str(), "sgt %d", &frequency);

    _map->setTimeUnit(frequency);
}

void Core::sst(std::string message)
{
    int frequency;
    sscanf(message.c_str(), "sst %d", &frequency);

    _map->setTimeUnit(frequency);
}

void Core::seg(std::string message)
{
    std::istringstream iss(message);
    std::string command;
    std::string teamName;
    iss >> command >> teamName;

    _map->setWiner(teamName);
}

void Core::smg(std::string message)
{
    std::string msg = message.substr(4);

    msg.erase(0, msg.find_first_not_of(" \t\n\r"));
    msg.erase(msg.find_last_not_of(" \t\n\r") + 1);

    _map->addServerMessage(msg);
}

void Core::suc()
{
    DEBUG_ERROR("Unknown command");
}

void Core::sbp()
{
    DEBUG_ERROR("Command parameter");
}
