/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_


#include <string>
#include <thread>
#include <atomic>
#include <memory>

#include "../API/Api.hpp"
#include "../SFML/SFML.hpp"
#include "../Map/Map.hpp"

namespace Zappy {

    class Core {
        public:
            Core(const std::string& host, int port);
            ~Core();

            void run();
        protected:
            void handleServerMessages();
            void updatePlayer(const std::string& message);
            void addPlayer(const std::string& message);
            void removePlayer(const std::string& message);

            std::string host;
            int port;
            std::atomic<bool> running;
            std::thread networkThread;

            std::unique_ptr<Api> api;
            std::unique_ptr<SFML> sfml;
            std::unique_ptr<Map> map;
    };

}

#endif /* !CORE_HPP_ */
