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

using namespace Zappy;

Api::Api(
    const std::string& host,
    int port
) : host(host),
    port(port),
    isRunning(true)
{
    client = protocol_client_create(host.c_str(), port);
    if (!client || !protocol_client_is_connected(client))
        throw std::runtime_error("Failed to connect to server");
    fetchDataThread = std::thread(&Api::fetchDataLoop, this);
    sendCommand("GRAPHIC");
}

Api::~Api()
{
    protocol_client_close(client);
}

void Api::sendCommand(const std::string &command)
{
    std::cout << "Sending command: " << command << std::endl;
    if (!protocol_client_send_packet(client, 0, command.c_str(), command.size()))
        std::cerr << "Failed to send command: " << command << std::endl;
}

std::string Api::getData()
{
    std::unique_lock<std::mutex> lock(dataMutex);
    dataCondVar.wait(lock, [this] { return !receivedData.empty(); });
    std::string data = receivedData.front();
    receivedData.pop();
    return data;
}

void Api::fetchDataFromServer()
{
    std::cout << "Fetching data from server" << std::endl;
    protocol_payload_t *payload = protocol_client_listen(client);
    if (payload) {
        std::lock_guard<std::mutex> lock(dataMutex);
        receivedData.push(std::string(reinterpret_cast<const char*>(payload->packet.data), DATA_SIZE));
        dataCondVar.notify_one();
    }
}

void Api::fetchDataLoop()
{
    while (isRunning) {
        fetchDataFromServer();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust sleep duration as needed
    }
}

void Api::requestMapSize() {
    sendCommand("msz\n");
}

void Api::requestTileContent(int x, int y) {
    sendCommand("bct " + std::to_string(x) + " " + std::to_string(y) + "\n");
}

void Api::requestAllTilesContent() {
    sendCommand("mct\n");
}

void Api::requestTeamsNames() {
    sendCommand("tna\n");
}

void Api::requestPlayerPosition(int playerNumber) {
    sendCommand("ppo #" + std::to_string(playerNumber) + "\n");
}

void Api::requestPlayerLevel(int playerNumber) {
    sendCommand("plv #" + std::to_string(playerNumber) + "\n");
}

void Api::requestPlayerInventory(int playerNumber) {
    sendCommand("pin #" + std::to_string(playerNumber) + "\n");
}

void Api::requestTimeUnit() {
    sendCommand("sgt\n");
}

void Api::modifyTimeUnit(int t) {
    sendCommand("sst " + std::to_string(t) + "\n");
}

void Api::endGame() {
    sendCommand("seg\n");
}

void Api::unknownCommand() {
    sendCommand("suc\n");
}

void Api::commandParameter() {
    sendCommand("sbp\n");
}
