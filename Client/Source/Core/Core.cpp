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
#include "../API/Events.h"


using namespace Zappy;

Core::Core(
    const std::string& host,
    int port
) : api(std::make_unique<Api>(host, port)),
    map(std::make_unique<Map>()),
    running(true),
    _hud(Hud())
{
    networkThread = std::thread(&Core::handleServerMessages, this);
    DEBUG_INFO("Core created with host: " + host + " and port: " + std::to_string(port));
}

Core::~Core()
{
    running = false;
    if (networkThread.joinable())
        networkThread.join();
    CloseWindow();
    api.reset();
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

        Camera3D camera = { 0 };
        camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;


        while (!WindowShouldClose() && running) {
            UpdateCamera(&camera, CAMERA_FIRST_PERSON);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
            map->draw(camera);
            EndMode3D();
            _hud.draw(map.get());
            DrawFPS(10, 10);
            EndDrawing();
        }

        CloseWindow();
        running = false;
    } catch (const std::exception &e) {
        throw MainException(e.what());
    }
    DEBUG_ERROR("Core stopped");
}

void Core::handleServerMessages() {
    try {
        while (running) {
            protocol_payload_t* payload = api->getData();
            if (!payload) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
            std::string message(reinterpret_cast<const char*>(payload->packet.data));
            DEBUG_INFO("Core received packet: " + message);
            if (message.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            if (message.find("WELCOME") == 0) {
                api->sendCommand("GRAPHIC");
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

void Core::msz(std::string message)
{
    int x, y;
    sscanf(message.c_str(), "msz %d %d", &x, &y);
    map->setSize(x, y);
}

void Core::bct(std::string message) {
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    sscanf(message.c_str(), "bct %d %d %d %d %d %d %d %d %d", &x, &y, &q0, &q1, &q2, &q3, &q4, &q5, &q6);
    map->updateTile(x, y, {q0, q1, q2, q3, q4, q5, q6});
}

void Core::tna(std::string message)
{
    std::string teamName = message.substr(4);

    teamName.erase(0, teamName.find_first_not_of(" \t\n\r"));
    teamName.erase(teamName.find_last_not_of(" \t\n\r") + 1);

    map->addTeam(teamName);
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
    const Team* team = map->getTeam(teamName);
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
    map->addPlayer(std::move(player));
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

    Player* player = map->getPlayer(playerNumber);
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

    Player* player = map->getPlayer(playerNumber);
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

    Player* player = map->getPlayer(playerNumber);
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

    Player* player = map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    // TODO: Implement pex
}

void Core::pbc(std::string message)
{
    std::istringstream iss(message);
    std::string command;
    int playerNumber;
    std::string msg;
    iss >> command >> playerNumber;
    std::getline(iss, msg);

    Player* player = map->getPlayer(playerNumber);
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
    while (iss >> playerNumber) {
        players.push_back(playerNumber);
    }
    DEBUG_INFO("Incantation started at " + std::to_string(x) + " " + std::to_string(y) + " with level " + std::to_string(level) + " and players: " + std::to_string(players.size()));
    // TODO: Implement pic
}

void Core::pie(std::string message)
{
    int x, y, result;
    sscanf(message.c_str(), "pie %d %d %d", &x, &y, &result);

    DEBUG_INFO("Incantation ended at " + std::to_string(x) + " " + std::to_string(y) + " with result: " + std::to_string(result));
    // TODO: Implement pie
}

void Core::pfk(std::string message)
{
    int playerNumber;
    sscanf(message.c_str(), "pfk %d", &playerNumber);

    Player* player = map->getPlayer(playerNumber);
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

    Player* player = map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    player->removeResource(static_cast<Zappy::Resources::Type>(resource), 1);
    std::pair<int, int> pos = player->getPosition();
    Tile* tile = map->getTile(pos.first, pos.second);
    if (!tile) {
        DEBUG_ERROR("Tile not found at " + std::to_string(pos.first) + " " + std::to_string(pos.second));
        return;
    }
    tile->addResource(static_cast<Zappy::Resources::Type>(resource), 1);
}

void Core::pgt(std::string message)
{
    int playerNumber, resource;
    sscanf(message.c_str(), "pgt %d %d", &playerNumber, &resource);

    Player* player = map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    player->addResource(static_cast<Zappy::Resources::Type>(resource), 1);
    std::pair<int, int> pos = player->getPosition();
    Tile* tile = map->getTile(pos.first, pos.second);
    if (!tile) {
        DEBUG_ERROR("Tile not found at " + std::to_string(pos.first) + " " + std::to_string(pos.second));
        return;
    }
    tile->removeResource(static_cast<Zappy::Resources::Type>(resource), 1);
}

void Core::pdi(std::string message)
{
    int playerNumber;
    sscanf(message.c_str(), "pdi %d", &playerNumber);

    Player* player = map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    std::pair<int, int> pos = player->getPosition();
    Tile* tile = map->getTile(pos.first, pos.second);
    if (!tile) {
        DEBUG_ERROR("Tile not found at " + std::to_string(pos.first) + " " + std::to_string(pos.second));
        return;
    }
    //tile->addResource(Zappy::Resources::Type::FOOD, 1);
    map->removePlayer(playerNumber);
}

void Core::enw(std::string message)
{
    int eggNumber, playerNumber, x, y;
    sscanf(message.c_str(), "enw %d %d %d %d", &eggNumber, &playerNumber, &x, &y);

    Player* player = map->getPlayer(playerNumber);
    if (!player) {
        DEBUG_ERROR("Player not found: " + std::to_string(playerNumber));
        return;
    }
    const Team* team = player->getTeam();
    if (!team) {
        DEBUG_ERROR("Team not found for player: " + std::to_string(playerNumber));
        return;
    }

    map->addEgg(std::make_unique<Egg>(
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

    Egg* egg = map->getEgg(eggNumber);
    if (!egg) {
        DEBUG_ERROR("Egg not found: " + std::to_string(eggNumber));
        return;
    }

    map->removeEgg(eggNumber);
    // TODO: Implement ebo
}

void Core::edi(std::string message)
{
    int eggNumber;
    sscanf(message.c_str(), "edi %d", &eggNumber);

    map->removeEgg(eggNumber);
}

void Core::sgt(std::string message)
{
    int frequency;
    sscanf(message.c_str(), "sgt %d", &frequency);

    map->setTimeUnit(frequency);
}

void Core::sst(std::string message)
{
    int frequency;
    sscanf(message.c_str(), "sst %d", &frequency);

    map->setTimeUnit(frequency);
}

void Core::seg(std::string message)
{
    std::istringstream iss(message);
    std::string command;
    std::string teamName;
    iss >> command >> teamName;

    map->setWiner(teamName);
}

void Core::smg(std::string message)
{
    std::string msg = message.substr(4);

    msg.erase(0, msg.find_first_not_of(" \t\n\r"));
    msg.erase(msg.find_last_not_of(" \t\n\r") + 1);

    map->addServerMessage(msg);
}

void Core::suc()
{
    DEBUG_ERROR("Unknown command");
}

void Core::sbp()
{
    DEBUG_ERROR("Command parameter");
}
