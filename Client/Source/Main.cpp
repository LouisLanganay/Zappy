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
    std::cout << "EXAMPLE: ./zappy_gui -p 4242 -h 192.0.0.1" << std::endl;

    return return_value;
}

int main(int ac, char **av)
{
    try {
        if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h"))
            return displayHelp(0);
        if (ac != 5)
            return displayHelp(84);
        if (std::string(av[1]) != "-p" || std::string(av[3]) != "-h")
            return displayHelp(84);
        if (std::string(av[2]).find_first_not_of("0123456789") != std::string::npos)
            return displayHelp(84);
        if (std::string(av[4]).find_first_not_of("0123456789.") != std::string::npos)
            return displayHelp(84);
        Zappy::Core core(av[4], std::stoi(av[2]));
        core.run();
        std::cout << "Exiting..." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
