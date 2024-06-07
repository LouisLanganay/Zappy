/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** HudRight
*/

#ifndef HUDRIGHT_HPP_
#define HUDRIGHT_HPP_

#include <raylib.h>
#include <string>
#include <vector>
#include <sstream>
#include "../Team/Team.hpp"
#include "../Map/Map.hpp"
#include "AHud.hpp"

namespace Zappy {
    class HudRight : public AHud {
        public:
            HudRight();
            void draw(Map *map) override;

        private:
            int _playerIndex = 0;
            int _selectedPlayer = -1;

            void _drawPlayersBroadcasts(Map *map, float &y);
    };
}

#endif /* !HUDRIGHT_HPP_ */
