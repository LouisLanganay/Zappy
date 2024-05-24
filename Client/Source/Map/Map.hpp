/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <SFML/Graphics.hpp>

namespace Zappy {
    class Map {
        public:
            Map();
            void update(const std::string& data);
            const sf::Drawable& getDrawable() const;

        private:
            sf::VertexArray mapVertices;
    };
};

#endif /* !MAP_HPP_ */
