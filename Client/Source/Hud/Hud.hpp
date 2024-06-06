/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Hud
*/

#ifndef HUD_HPP_
#define HUD_HPP_

#include <raylib.h>
#include <string>
#include <vector>
#include <sstream>
#include "../Team/Team.hpp"
#include "../Map/Map.hpp"

namespace Zappy {
    class Hud {
        public:
            Hud();
            void draw(Map *map);

        private:
            const float _titleSize = 40;
            const float _textSize = 35;
            const float _hudPadding = 20;
            const float _hudWidth = 400;

            int _playerIndex = 0;
            int _selectedPlayer = -1;

            void drawTextWrapped(
                const std::string &text,
                float x,
                float &y,
                float maxWidth,
                float fontSize,
                const Color &color,
                bool underline
            );

            void drawSectionTitle(const std::string &title, float &y);

            void drawTeams(Map *map, float &y);
            void drawServerInfos(Map *map, float &y);
            void drawResources(Map *map, float &y);
            void drawPlayers(Map *map, float &y);
            void drawPlayerInfos(Player *player, float &y);

            std::string typeToString(Resources::Type type);
            std::string orientationToString(Orientation orientation);
    };
}

#endif /* !HUD_HPP_ */
