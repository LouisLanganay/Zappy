/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** NetworkManager
*/

#ifndef NETWORKMANAGER_HPP_
#define NETWORKMANAGER_HPP_

#include <thread>
#include "../API/Api.hpp"

namespace Zappy {
    class NetworkManager {
        public:
            NetworkManager(const std::string& host, int port);
            ~NetworkManager();
            void receiveData();

        private:
            Api api;
            std::thread networkThread;
            bool running;

            void networkLoop();
    };
}

#endif /* !NETWORKMANAGER_HPP_ */
