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
            void endGame();
            void unknownCommand();
            void commandParameter();

        private:
            std::queue<std::string> receivedData;
            std::mutex dataMutex;
            std::condition_variable dataCondVar;
            std::string host;
            int port;
            protocol_client_t *client;
            std::thread fetchDataThread;
            bool isRunning;
            void fetchDataLoop();

    };
}

#endif /* !API_HPP_ */
