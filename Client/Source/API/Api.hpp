/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Api
*/

#ifndef API_HPP_
#define API_HPP_

#include <queue>
#include <mutex>
#include <condition_variable>
extern "C" {
    #include "../../../libs/protocol/include/protocol/client.h"
}
#include <thread>
#include <iostream>
#include <string>
#include <chrono>

namespace Zappy {
    class Api {
        public:
            Api(const std::string& host, int port);
            ~Api();

            void sendCommand(std::string command);
            std::string getData();
            void fetchDataFromServer();

            void requestMapSize();
            void requestTileContent(int x, int y);
            void requestAllTilesContent();
            void requestTeamsNames();
            void requestPlayerPosition(int playerNumber);
            void requestPlayerLevel(int playerNumber);
            void requestPlayerInventory(int playerNumber);
            void requestTimeUnit();
            void modifyTimeUnit(int t);

        private:
            std::queue<std::string> _receivedData;
            std::mutex _dataMutex;
            std::condition_variable _dataCondVar;
            std::string _host;
            int _port;
            protocol_client_t *_client;
            std::thread _fetchDataThread;
            bool _isRunning;
            void fetchDataLoop();

    };
}

#endif /* !API_HPP_ */
