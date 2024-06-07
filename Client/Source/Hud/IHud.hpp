/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IHud
*/

#ifndef IHUD_HPP_
#define IHUD_HPP_

#include <utility>

namespace Zappy {
    class Map;

    class IHud {
        public:
            virtual ~IHud() = default;
            virtual void draw(Map *map) = 0;

            virtual void setHudWidth(float width) = 0;
            virtual float getHudWidth() = 0;

            virtual void setHudHeight(float height) = 0;
            virtual float getHudHeight() = 0;

            virtual void setHudPos(std::pair<float, float> pos) = 0;
    };
}

#endif /* !IHUD_HPP_ */
