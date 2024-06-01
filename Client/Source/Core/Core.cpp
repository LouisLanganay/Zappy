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
    CloseWindow();
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
            map->draw();
            EndMode3D();
            DrawFPS(10, 10);
            EndDrawing();
        }

        CloseWindow();
        running = false;
    } catch (const std::exception &e) {
        throw MainException(e.what());
    }
}

void Core::handleServerMessages() {
    try {
        while (running) {
            protocol_payload_t* payload = api->getData();
            if (!payload) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            DEBUG_INFO("Core received packet of type: " + std::to_string(payload->packet.type));

            switch (payload->packet.type) {
                case EVT_MAP_SIZE: {
                    map_size_t mapSize;
                    std::memcpy(&mapSize, payload->packet.data, sizeof(map_size_t));
                    map->setSize(mapSize.width, mapSize.height);
                    break;
                }
                case EVT_TILE_CONTENT: {
                    DEBUG_INFO("Received tile content");
                    tile_content_t tileContent;
                    std::memcpy(&tileContent, payload->packet.data, sizeof(tile_content_t));
                    std::vector<int> resources(tileContent.resources, tileContent.resources + 7);
                    map->updateTile(tileContent.x, tileContent.y, resources);
                    break;
                }
                case EVT_MAP_CONTENT: {
                    map_content_t mapContent;
                    std::memcpy(&mapContent, payload->packet.data, sizeof(map_content_t));
                    for (int i = 0; i < mapContent.width * mapContent.height; ++i) {
                        tile_content_t tileContent = mapContent.tiles[i];
                        std::vector<int> resources(tileContent.resources, tileContent.resources + 7);
                        map->updateTile(tileContent.x, tileContent.y, resources);
                    }
                    break;
                }
                case EVT_TEAMS_NAME: {
                    teams_name_t teamsName;
                    std::memcpy(&teamsName, payload->packet.data, sizeof(teams_name_t));
                    std::vector<std::string> teams;
                    // TODO: Implement team names
                    teams.push_back("test");
                    teams.push_back("test2");
                    map->setTeams(teams);
                    break;
                }
                case EVT_PLAYER_ADD: {
                    player_add_t playerAdd;
                    std::memcpy(&playerAdd, payload->packet.data, sizeof(player_add_t));
                    Orientation orient = static_cast<Orientation>(playerAdd.orientation);
                    const Team* team = map->getTeam(playerAdd.teamName);
                    if (!team)
                        break;
                    std::unique_ptr<Player> player = std::make_unique<Player>(
                        playerAdd.playerNumber,
                        std::make_unique<Team>(*team),
                        orient,
                        playerAdd.level
                    );
                    player->setPosition(playerAdd.x, playerAdd.y);
                    map->addPlayer(std::move(player));
                    break;
                }
                case EVT_PLAYER_POSITION: {
                    player_position_t playerPos;
                    std::memcpy(&playerPos, payload->packet.data, sizeof(player_position_t));
                    Player* player = map->getPlayer(playerPos.playerNumber);
                    if (player)
                        player->setPosition(playerPos.x, playerPos.y);
                    break;
                }
                case EVT_PLAYER_LEVEL: {
                    player_level_t playerLevel;
                    std::memcpy(&playerLevel, payload->packet.data, sizeof(player_level_t));
                    Player* player = map->getPlayer(playerLevel.playerNumber);
                    if (player)
                        player->setLevel(playerLevel.level);
                    break;
                }
                case EVT_PLAYER_INVENTORY: {
                    player_inventory_t playerAdd;
                    std::memcpy(&playerAdd, payload->packet.data, sizeof(player_inventory_t));
                    Player* player = map->getPlayer(playerAdd.playerNumber);
                    if (!player)
                        break;
                    std::vector<int> resources(playerAdd.resources, playerAdd.resources + 7);
                    for (int i = 0; i < 7; ++i)
                        player->setResource(
                            static_cast<Zappy::Resources::Type>(i),
                            resources[i]
                        );
                    break;
                }
                case EVT_EXPULSION: {
                    expulsion_t expulsion;
                    std::memcpy(&expulsion, payload->packet.data, sizeof(expulsion_t));
                    // TODO: Implement player expulsion
                    break;
                }
                case EVT_BROADCAST: {
                    broadcast_t broadcast;
                    std::memcpy(&broadcast, payload->packet.data, sizeof(broadcast_t));
                    Player* player = map->getPlayer(broadcast.playerNumber);
                    if (player)
                        player->addBroadcast(broadcast.message);
                    break;
                }
                case EVT_INCANTATION_START: {
                    incantation_start_t incantationStart;
                    std::memcpy(&incantationStart, payload->packet.data, sizeof(incantation_start_t));
                    // TODO: Implement incantation start
                    break;
                }
                case EVT_INCANTATION_END: {
                    incantation_end_t incantationEnd;
                    std::memcpy(&incantationEnd, payload->packet.data, sizeof(incantation_end_t));
                    // TODO: Implement incantation end
                    break;
                }
                case EVT_PLAYER_EGG_LAYING: {
                    player_egg_laying_t eggLaying;
                    std::memcpy(&eggLaying, payload->packet.data, sizeof(player_egg_laying_t));
                    // TODO: Implement player egg laying
                    break;
                }
                case EVT_RESOURCE_DROP: {
                    resource_drop_t resourceDrop;
                    std::memcpy(&resourceDrop, payload->packet.data, sizeof(resource_drop_t));
                    Player* player = map->getPlayer(resourceDrop.playerNumber);
                    if (!player)
                        break;
                    Tile* tile = map->getTile(player->getPosition().first, player->getPosition().second);
                    if (!tile)
                        break;
                    player->removeResource(
                        static_cast<Zappy::Resources::Type>(resourceDrop.resourceType),
                        1
                    );
                    tile->addResource(
                        static_cast<Zappy::Resources::Type>(resourceDrop.resourceType),
                        1
                    );
                    break;
                }
                case EVT_RESOURCE_COLLECT: {
                    resource_drop_t resourceDrop;
                    std::memcpy(&resourceDrop, payload->packet.data, sizeof(resource_drop_t));
                    Player* player = map->getPlayer(resourceDrop.playerNumber);
                    if (!player)
                        break;
                    Tile* tile = map->getTile(player->getPosition().first, player->getPosition().second);
                    if (!tile)
                        break;
                    player->addResource(
                        static_cast<Zappy::Resources::Type>(resourceDrop.resourceType),
                        1
                    );
                    tile->addResource(
                        static_cast<Zappy::Resources::Type>(resourceDrop.resourceType),
                        -1
                    );
                    break;
                }
                case EVT_PLAYER_DEATH: {
                    player_death_t playerDeath;
                    std::memcpy(&playerDeath, payload->packet.data, sizeof(player_death_t));
                    map->removePlayer(playerDeath.playerNumber);
                    break;
                }
                case EVT_EGG_LAID: {
                    egg_laid_t eggLaid;
                    std::memcpy(&eggLaid, payload->packet.data, sizeof(egg_laid_t));
                    // TODO: Implement egg laid
                    break;
                }
                case EVT_EGG_CONNECT: {
                    egg_connect_t eggConnect;
                    std::memcpy(&eggConnect, payload->packet.data, sizeof(egg_connect_t));
                    // TODO: Implement egg connect
                    break;
                }
                case EVT_EGG_DEATH: {
                    egg_death_t eggDeath;
                    std::memcpy(&eggDeath, payload->packet.data, sizeof(egg_death_t));
                    // TODO: Implement egg death
                    break;
                }
                case EVT_TIME_UNIT_REQUEST: {
                    time_unit_request_t timeUnitRequest;
                    std::memcpy(&timeUnitRequest, payload->packet.data, sizeof(time_unit_request_t));
                    // TODO: Implement time unit request
                    break;
                }
                case EVT_TIME_UNIT_CHANGE: {
                    time_unit_change_t timeUnitChange;
                    std::memcpy(&timeUnitChange, payload->packet.data, sizeof(time_unit_change_t));
                    // TODO: Implement time unit change
                    break;
                }
                case EVT_GAME_END: {
                    game_end_t gameEnd;
                    std::memcpy(&gameEnd, payload->packet.data, sizeof(game_end_t));
                    // TODO: Implement game end
                    break;
                }
                case EVT_SERVER_MESSAGE: {
                    server_message_t serverMessage;
                    std::memcpy(&serverMessage, payload->packet.data, sizeof(server_message_t));
                    map->addServerMessage(serverMessage.message);
                    break;
                }
                case EVT_UNKNOWN_COMMAND: {
                    DEBUG_ERROR("Unknown command received from server");
                    break;
                }
                case EVT_BAD_PARAMETER: {
                    DEBUG_ERROR("Bad parameter received from server");
                    break;
                }
                default:
                    DEBUG_ERROR("Unknown event type: " + payload->packet.type);
                    break;
            }
        }
    } catch (const std::exception& e) {
        throw MainException(e.what());
    }
}
