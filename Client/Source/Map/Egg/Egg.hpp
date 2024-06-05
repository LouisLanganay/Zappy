/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#ifndef EGG_HPP_
#define EGG_HPP_

#include <utility>
#include <memory>
#include <raylib.h>
#include "../Team/Team.hpp"

namespace Zappy {
    class Egg {
        public:
            Egg(int eggNumber, int playerNumber, int x, int y, std::unique_ptr<Team> team);

            int getEggNumber() const;
            int getPlayerNumber() const;
            std::pair<int, int> getPosition() const;

            void setHatched(bool hatched);
            bool isHatched() const;

            void draw();

            const Team* getTeam() const;

        private:
            int eggNumber;
            int playerNumber;
            std::pair<int, int> position;
            bool hatched;
            std::unique_ptr<Team> _team;
    };
}

#endif /* !EGG_HPP_ */
