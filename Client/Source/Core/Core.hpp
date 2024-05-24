/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <string>
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

        private:
            void handleEvents();
            void update();
            void render();

            std::unique_ptr<Api> api;
            std::unique_ptr<SFML> sfml;
            std::unique_ptr<Map> map;
    };
}

#endif /* !CORE_HPP_ */
