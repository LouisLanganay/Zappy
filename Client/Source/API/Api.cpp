/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Api
*/

#include "Api.hpp"
#include <string>
#include "Api.hpp"
#include <string>
#include <iostream>
#include <thread>
#include "Debug.hpp"
#include "../Exceptions.hpp"
#include "Events.h"
#include <cstring>

using namespace Zappy;

Api::Api(
    const std::string& host,
    int port
) : host(host),
    port(port),
    isRunning(true),
    dataMutex()
{
    try {
        DEBUG_INFO("Creating API with host: " + host + " and port: " + std::to_string(port));
        client = protocol_client_create(host.c_str(), port);
        if (!client || !protocol_client_is_connected(client))
            throw std::runtime_error("Failed to connect to server");
        DEBUG_SUCCESS("Connected to server");
        fetchDataThread = std::thread(&Api::fetchDataLoop, this);
        sendCommand("GRAPHIC\n");
    } catch (const std::exception &e) {
        throw ApiException(e.what());
    }
}

Api::~Api()
{
    std::cout << "Api destructor" << std::endl;
    isRunning = false;
    if (fetchDataThread.joinable())
        fetchDataThread.join();
    protocol_client_close(client);
}

void Api::sendCommand(std::string command)
{
    if (!protocol_client_send_packet(client, 1, command.c_str(), strlen(command.c_str())))
        throw ApiException("Failed to send command to server");
}

protocol_payload_t* Api::getData()
{
    std::unique_lock<std::mutex> lock(dataMutex);
    dataCondVar.wait(lock, [this] { return !receivedData.empty(); });
    protocol_payload_t* payload = receivedData.front();
    receivedData.pop();
    return payload;
}

void Api::fetchDataFromServer()
{
    protocol_payload_t *payload;

    while (
        protocol_client_listen(client) &&
        !TAILQ_EMPTY(&client->payloads) &&
        isRunning
    ) {
        payload = TAILQ_FIRST(&client->payloads);
        TAILQ_REMOVE(&client->payloads, payload, entries);

        if (payload) {
            {
                std::lock_guard<std::mutex> lock(dataMutex);
                receivedData.push(payload);
                dataCondVar.notify_one();
            }
        }
    }
}

void Api::fetchDataLoop()
{
    while (isRunning) {
        fetchDataFromServer();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Api::requestMapSize() {
    //sendCommand("msz\n");
}

void Api::requestTileContent(int x, int y) {
    //sendCommand("bct " + std::to_string(x) + " " + std::to_string(y) + "\n");
}

void Api::requestAllTilesContent() {
    //sendCommand("mct\n");
}

void Api::requestTeamsNames() {
    //sendCommand("tna\n");
}

void Api::requestPlayerPosition(int playerNumber) {
    //sendCommand("ppo #" + std::to_string(playerNumber) + "\n");
}

void Api::requestPlayerLevel(int playerNumber) {
    //sendCommand("plv #" + std::to_string(playerNumber) + "\n");
}

void Api::requestPlayerInventory(int playerNumber) {
    //sendCommand("pin #" + std::to_string(playerNumber) + "\n");
}

void Api::requestTimeUnit() {
    //sendCommand("sgt\n");
}

void Api::modifyTimeUnit(int t) {
    //sendCommand("sst " + std::to_string(t) + "\n");
}

void Api::endGame() {
    //sendCommand("seg\n");
}

void Api::unknownCommand() {
    //sendCommand("suc\n");
}

void Api::commandParameter() {
    //sendCommand("sbp\n");
}
