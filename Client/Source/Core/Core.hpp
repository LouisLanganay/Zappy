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

namespace Zappy {
    class Core {
        public:
            Core(std::string host, int port);
            ~Core();
    };
}

#endif /* !CORE_HPP_ */
