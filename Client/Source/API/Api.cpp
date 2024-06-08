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
) : _host(host),
    _port(port),
    _isRunning(true),
    _dataMutex()
{
    try {
        DEBUG_INFO("Creating API with host: " + host + " and port: " + std::to_string(port));
        _client = protocol_client_create(host.c_str(), port);
        if (!_client || !protocol_client_is_connected(_client))
            throw std::runtime_error("Failed to connect to server");
        DEBUG_SUCCESS("Connected to server");
        _fetchDataThread = std::thread(&Api::fetchDataLoop, this);
        sendCommand("GRAPHIC\n");
    } catch (const std::exception &e) {
        throw ApiException(e.what());
    }
}

Api::~Api()
{
    if (_fetchDataThread.joinable())
        _fetchDataThread.join();
    protocol_client_close(_client);
}

void Api::stop()
{
    _isRunning = false;
    _dataCondVar.notify_all();
    if (_fetchDataThread.joinable())
        _fetchDataThread.join();
}

bool Api::isRunning() const
{
    return _isRunning;
}

void Api::sendCommand(std::string command)
{
    DEBUG_INFO("Sending command: " + command);
    if (!protocol_client_send(_client, "%s", command.c_str()))
        throw ApiException("Failed to send command to server");
    DEBUG_SUCCESS("Command sent");
}

std::string Api::getData()
{
    std::unique_lock<std::mutex> lock(_dataMutex);
    _dataCondVar.wait(lock, [this] { return !_receivedData.empty() || !_isRunning; });
    if (!_isRunning && _receivedData.empty())
        return "";
    std::string message = _receivedData.front();
    _receivedData.pop();
    return message;
}

void Api::fetchDataFromServer()
{
    protocol_payload_t *payload;

    protocol_client_listen(_client);
    while (!TAILQ_EMPTY(&_client->payloads)) {
        payload = TAILQ_FIRST(&_client->payloads);
        TAILQ_REMOVE(&_client->payloads, payload, entries);
        char *message = payload->message;

        if (message) {
            std::string messageStr(message);
            {
                std::lock_guard<std::mutex> lock(_dataMutex);
                _receivedData.push(messageStr);
                _dataCondVar.notify_one();
            }
        }
        free(payload);
    }
}

void Api::fetchDataLoop()
{
    while (_isRunning && protocol_client_is_connected(_client)) {
        fetchDataFromServer();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Api::requestMapSize()
{
    sendCommand("msz\n");
}

void Api::requestTileContent(int x, int y)
{
    sendCommand("bct " + std::to_string(x) + " " + std::to_string(y) + "\n");
}

void Api::requestAllTilesContent()
{
    sendCommand("mct\n");
}

void Api::requestTeamsNames()
{
    sendCommand("tna\n");
}

void Api::requestPlayerPosition(int playerNumber)
{
    sendCommand("ppo " + std::to_string(playerNumber) + "\n");
}

void Api::requestPlayerLevel(int playerNumber)
{
    sendCommand("plv " + std::to_string(playerNumber) + "\n");
}

void Api::requestPlayerInventory(int playerNumber)
{
    sendCommand("pin " + std::to_string(playerNumber) + "\n");
}

void Api::requestTimeUnit()
{
    sendCommand("sgt\n");
}

void Api::modifyTimeUnit(int t)
{
    sendCommand("sst " + std::to_string(t) + "\n");
}
