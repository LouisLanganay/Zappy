/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Team
*/

#ifndef TEAM_HPP_
#define TEAM_HPP_

#include <string>
#include "raylib.h"

namespace Zappy {
    class Team {
        public:
            Team(const std::string& name, const Color& color);

            std::string getName() const;
            Color getColor() const;

        private:
            std::string name;
            Color color;
    };
};

#endif /* !TEAM_HPP_ */
