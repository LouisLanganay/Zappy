/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

namespace Zappy {
    class SFML {
        public:
            SFML();
            ~SFML();
            void processEvents();
            void clear();
            void draw(const sf::Drawable& drawable);
            void display();
            bool isOpen() const;

        private:
            sf::RenderWindow window;
    };
}

#endif /* !SFML_HPP_ */