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

            Color _titleColor = { 17, 42, 70, 255 };
            Color _textColor = { 29, 66, 108, 255 };

            Color _backgroundColor = { 188, 221, 255, 255 };
    };
}

#endif /* !HUDRIGHT_HPP_ */
