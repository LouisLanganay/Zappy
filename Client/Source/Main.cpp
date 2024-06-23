/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Main
*/

#include <iostream>
#include "Core.hpp"
#include "Exceptions.hpp"

int displayHelp(int return_value)
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    std::cout << "\tport\t is the port number" << std::endl;
    std::cout << "\tmachine\t is the hostname of the server" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "EXAMPLE: ./zappy_gui -p 4242 -h 127.0.0.1" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "KEYBINDINGS:" << std::endl;
    std::cout << "\tZ\tMove forward" << std::endl;
    std::cout << "\tQ\tTurn left" << std::endl;
    std::cout << "\tS\tMove backward" << std::endl;
    std::cout << "\tD\tTurn right" << std::endl;
    std::cout << "\tO\tScroll up player list" << std::endl;
    std::cout << "\tP\tScroll down player list" << std::endl;
    std::cout << "\tENTER\tSelect player" << std::endl;
    std::cout << "\tI\tIncrease time unit" << std::endl;
    std::cout << "\tU\tDecrease time unit" << std::endl;


    return return_value;
}

int main(int ac, char **av) {
    try {
        if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h")) {
            return displayHelp(0);
        }

        if (ac != 5) {
            return displayHelp(84);
        }

        std::string portStr, hostStr;
        for (int i = 1; i < ac; i += 2) {
            std::string arg(av[i]);
            if (arg == "-p") {
                if (i + 1 < ac) {
                    portStr = av[i + 1];
                } else {
                    return displayHelp(84);
                }
            } else if (arg == "-h") {
                if (i + 1 < ac) {
                    hostStr = av[i + 1];
                } else {
                    return displayHelp(84);
                }
            } else {
                return displayHelp(84);
            }
        }

        if (portStr.empty() || hostStr.empty()) {
            return displayHelp(84);
        }

        if (portStr.find_first_not_of("0123456789") != std::string::npos) {
            return displayHelp(84);
        }

        if (hostStr.find_first_not_of("0123456789.") != std::string::npos) {
            return displayHelp(84);
        }

        Zappy::Core core(hostStr, std::stoi(portStr));
        core.run();
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
