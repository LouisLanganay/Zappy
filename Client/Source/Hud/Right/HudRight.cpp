/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** HudRight
*/

#include "HudRight.hpp"

using namespace Zappy;

HudRight::HudRight() : AHud({1000, 500}, {0, 0})
{
}

void HudRight::draw(Map *map)
{
    float y = 0;
    AHud::draw(map);
    DrawRectangle(
        _hudPos.first,
        _hudPos.second,
        _hudWidth == 0 ? GetScreenWidth() : _hudWidth,
        _hudHeight == 0 ? GetScreenHeight() : _hudHeight,
        Fade(_backgroundColor, 0.5f)
    );
    DrawRectangleLines(
        _hudPos.first,
        _hudPos.second,
        _hudWidth == 0 ? GetScreenWidth() : _hudWidth,
        _hudHeight == 0 ? GetScreenHeight() : _hudHeight,
        Fade(_backgroundColor, 1.0f)
    );

    _drawPlayersBroadcasts(map, y);
}

void HudRight::_drawPlayersBroadcasts(Map *map, float &y)
{
    drawSectionTitle("Players broadcasts", y, _titleColor);
    for (auto &player : map->getPlayers()) {
        std::string message;
        if (player->getBroadcast().empty())
            continue;
        message = std::to_string(player->getPlayerNumber()) + ": " + player->getBroadcast();
        drawTextWrapped(
            message.c_str(),
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            player->getTeam()->getColor(),
            false,
            _textFont
        );
    }
}
