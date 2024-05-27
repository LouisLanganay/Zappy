/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Core.hpp"
#include "Debug.hpp"

using namespace Zappy;

Core::Core(
    const std::string& host,
    int port
) : api(std::make_unique<Api>(host, port)),
    sfml(std::make_unique<SFML>()),
    map(std::make_unique<Map>()),
    running(true)
{
    networkThread = std::thread(&Core::handleServerMessages, this);
    DEBUG_INFO("Core created with host: " + host + " and port: " + std::to_string(port));
}

Core::~Core()
{
    running = false;
    if (networkThread.joinable())
        networkThread.join();
}

void Core::run() {
    DEBUG_INFO("Core is running");
    while (sfml->isOpen()) {
        sfml->processEvents();
        sfml->clear();
        sfml->draw(map->getDrawable());
        sfml->display();
    }
    running = false;
}

void Core::handleServerMessages() {
    while (running) {
        std::string message = api->getData();
        DEBUG_INFO("Received message: " + message);
        if (message.empty())
            continue;

        if (message.find("pnw") == 0)
            addPlayer(message);
        if (message.find("ppo") == 0 || message.find("plv") == 0 || message.find("pin") == 0)
            updatePlayer(message);
        if (message.find("pdi") == 0)
            removePlayer(message);
        if (message.find("bct") == 0) {
            int x, y, q0, q1, q2, q3, q4, q5, q6;
            sscanf(message.c_str(), "bct %d %d %d %d %d %d %d %d %d", &x, &y, &q0, &q1, &q2, &q3, &q4, &q5, &q6);
            map->updateTile(x, y, {q0, q1, q2, q3, q4, q5, q6});
        }
        if (message.find("msz") == 0) {
            int x, y;
            sscanf(message.c_str(), "msz %d %d", &x, &y);
            map->setSize(x, y);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Core::addPlayer(const std::string& message) {
    int playerNumber, x, y, orientation, level;
    char teamName[50];
    sscanf(message.c_str(), "pnw #%d %d %d %d %d %s", &playerNumber, &x, &y, &orientation, &level, teamName);

    Orientation orient = static_cast<Orientation>(orientation);
    auto player = std::make_unique<Player>(playerNumber, teamName, orient, level);
    map->addPlayer(std::move(player));
}

void Core::updatePlayer(const std::string& message) {
    int playerNumber, x, y, orientation, level;
    sscanf(message.c_str(), "ppo #%d %d %d %d", &playerNumber, &x, &y, &orientation);
    sscanf(message.c_str(), "plv #%d %d", &playerNumber, &level);

    Player* player = map->getPlayer(playerNumber);
    if (player) {
        if (message.find("ppo") == 0) {
            Orientation orient = static_cast<Orientation>(orientation);
            player->setOrientation(orient);
        } else if (message.find("plv"))
            player->setLevel(level);
        else if (message.find("pin")) {
            int q0, q1, q2, q3, q4, q5, q6;
            sscanf(message.c_str(), "pin #%d %d %d %d %d %d %d %d %d", &playerNumber, &x, &y, &q0, &q1, &q2, &q3, &q4, &q5, &q6);
            player->addResource(new Resources::Linemate(), q0);
            player->addResource(new Resources::Deraumere(), q1);
            player->addResource(new Resources::Sibur(), q2);
            player->addResource(new Resources::Mendiane(), q3);
            player->addResource(new Resources::Phiras(), q4);
            player->addResource(new Resources::Thystame(), q5);
        }
    }
}

void Core::removePlayer(const std::string& message) {
    int playerNumber;
    sscanf(message.c_str(), "pdi #%d", &playerNumber);
    map->removePlayer(playerNumber);
}
