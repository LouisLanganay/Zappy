/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** NetworkManager
*/

#include "NetworkManager.hpp"

using namespace Zappy;

NetworkManager::NetworkManager(
    const std::string& host,
    int port
) : api(host, port),
    networkThread(&NetworkManager::networkLoop, this)
{

}

NetworkManager::~NetworkManager()
{
    if (networkThread.joinable())
        networkThread.join();
}

void NetworkManager::receiveData()
{
}

void NetworkManager::networkLoop() {
    while (true) {
        api.fetchDataFromServer();
        // Stocker les données reçues
    }
}
