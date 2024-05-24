/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Core.hpp"

using namespace Zappy;

Core::Core(
    const std::string& host,
    int port
) : api(std::make_unique<Api>(host, port)),
    sfml(std::make_unique<SFML>()),
    map(std::make_unique<Map>())
{
    std::cout << "Core created with host: " << host << " and port: " << port << std::endl;
}

Core::~Core()
{
}

void Core::run() {
    while (sfml->isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Core::handleEvents() {
    sfml->processEvents();
}

void Core::update() {
    map->update(api->getData());
}

void Core::render() {
    sfml->clear();
    sfml->draw(map->getDrawable());
    sfml->display();
}
