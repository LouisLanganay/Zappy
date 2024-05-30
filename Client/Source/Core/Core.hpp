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
            void handleServerMessages();

        protected:
            void addPlayer(const std::string& message);
            void updatePlayer(const std::string& message);
            void removePlayer(const std::string& message);

            std::unique_ptr<Api> api;
            std::unique_ptr<Map> map;
            std::thread networkThread;
            bool running;
            bool debug;
    };

}

#endif /* !CORE_HPP_ */
