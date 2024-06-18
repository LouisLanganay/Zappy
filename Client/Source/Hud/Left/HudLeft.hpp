/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** HudLeft
*/

#ifndef HUDLEFT_HPP_
#define HUDLEFT_HPP_

#include <raylib.h>
#include <string>
#include <vector>
#include <sstream>
#include "../Team/Team.hpp"
#include "../Map/Map.hpp"
#include "AHud.hpp"

namespace Zappy {
    class HudLeft : public AHud {
        public:
            HudLeft();
            void draw(Map *map) override;

        private:
            int _playerIndex = 0;
            int _selectedPlayer = -1;

            void _drawTeams(Map *map, float &y);
            void _drawServerInfos(Map *map, float &y);
            void _drawResources(Map *map, float &y);
            void _drawPlayers(Map *map, float &y);
            void _drawPlayerInfos(Player *player, float &y);

            Color _titleColor = { 17, 42, 70, 255 };
            Color _textColor = { 29, 66, 108, 255 };

            Color _backgroundColor = { 188, 221, 255, 255 };
    };
}

#endif /* !HUDLEFT_HPP_ */
