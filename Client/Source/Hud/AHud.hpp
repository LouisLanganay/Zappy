/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AHud
*/

#ifndef AHUD_HPP_
#define AHUD_HPP_

#include "IHud.hpp"
#include <raylib.h>
#include <string>
#include <vector>
#include <sstream>
#include "../Team/Team.hpp"
#include "../Map/Map.hpp"

namespace Zappy {
    class AHud : public IHud {
        public:
            virtual ~AHud() = default;
            void draw(Map *map) override = 0;

            void setHudWidth(float width) override;
            float getHudWidth() override;

            void setHudHeight(float height) override;
            float getHudHeight() override;

            void setHudPos(std::pair<float, float> pos) override;

        protected:
            AHud(
                std::pair<float, float> hudRes,
                std::pair<float, float> hudPos
            );

            virtual void drawTextWrapped(
                const std::string &text,
                float x,
                float &y,
                float maxWidth,
                float fontSize,
                const Color &color,
                bool underline
            );

            void drawSectionTitle(const std::string &title, float &y);

            virtual std::string typeToString(Resources::Type type);
            virtual std::string orientationToString(Orientation orientation);

            const float _titleSize = 40;
            const float _textSize = 35;
            const float _hudPadding = 20;
            float _hudWidth;
            float _hudHeight;
            std::pair<float, float> _hudPos;

            int _playerIndex = 0;
            int _selectedPlayer = -1;

            bool _sectionMargin = false;
    };
}

#endif /* !AHUD_HPP_ */
