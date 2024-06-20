/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** HudLeft
*/

#include "HudLeft.hpp"

using namespace Zappy;

HudLeft::HudLeft() : AHud({650, 0}, {20, 20})
{
}

void HudLeft::draw(Map *map)
{
    float y = 30;
    AHud::draw(map);

    DrawFPS(_hudPos.first + _hudPadding, _hudPos.second + _hudPadding);
    _drawTeams(map, y);
    _drawServerInfos(map, y);
    _drawPlayers(map, y);
    if (_selectedPlayer != -1)
        _drawPlayerInfos(map->getPlayer(_selectedPlayer), y);
    _drawResources(map, y);
}

void HudLeft::_drawTeams(Map *map, float &y)
{
    drawSectionTitle("Teams:", y);
    if (map->getTeams().empty()) {
        drawTextWrapped(
            "No teams",
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            BLACK,
            false
        );
    }
    for (auto &team : map->getTeams()) {
        drawTextWrapped(
            "- " + team->getName(),
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            team->getColor(),
            false
        );
    }
}

void HudLeft::_drawServerInfos(Map *map, float &y)
{
    drawSectionTitle("Server infos:", y);
    drawTextWrapped(
        "Time unit: " + std::to_string(map->getTimeUnit()),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
    drawTextWrapped(
        "Press 'I' to increase and 'U' to decrease",
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );

    drawTextWrapped(
        "Map size: " + std::to_string(map->getWidth()) + "x" + std::to_string(map->getHeight()),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
    std::string message = map->getServerMessage();
    drawTextWrapped(
        "Server message: " + (message.empty() ? "No message" : message),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
}

void HudLeft::_drawResources(Map *map, float &y)
{
    drawSectionTitle("Resources:", y);
    std::unordered_map<Resources::Type, int> resourcesTotal;
    for (auto &tiles : map->getTiles()) {
        for (auto &tile : tiles) {
            for (auto &resource : tile.getResources()) {
                resourcesTotal[resource.first] += resource.second;
            }
        }
    }
    for (auto &resource : resourcesTotal) {
        drawTextWrapped(
            "- " + typeToString(resource.first) + ": " + std::to_string(resource.second),
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            BLACK,
            false
        );
    }
    if (resourcesTotal.empty()) {
        drawTextWrapped(
            "No resources",
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            BLACK,
            false
        );
    }
}

void HudLeft::_drawPlayers(Map *map, float &y) {
    drawSectionTitle("Players:", y);
    const auto &players = map->getPlayers();
    if (players.empty()) {
        drawTextWrapped(
            "No players",
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            BLACK,
            false
        );
        return;
    }

    if (IsKeyPressed(KEY_O))
        _playerIndex = (_playerIndex + 1) % players.size();
    if (IsKeyPressed(KEY_P))
        _playerIndex = (_playerIndex - 1 + players.size()) % players.size();

    if (IsKeyPressed(KEY_ENTER)) {
        if (players[_playerIndex]->getPlayerNumber() != _selectedPlayer) {
            for (auto &player : players)
                player->setSelected(false);
            _selectedPlayer = players[_playerIndex]->getPlayerNumber();
            players[_playerIndex]->setSelected(true);
        } else {
            _selectedPlayer = -1;
            players[_playerIndex]->setSelected(false);
        }
    }

    for (size_t i = 0; i < players.size(); ++i) {
        const auto &player = players[i];
        if (player->getPlayerNumber() == _selectedPlayer) {
            Color color = player->getTeam()->getColor();
            DrawRectangle(
                _hudPadding - 5 + _hudPos.first,
                y - 3 + _hudPos.second + _hudPadding,
                _hudWidth - _hudPadding * 2,
                _textSize + 10,
                Fade(color, 0.2f)
            );
        }
        if (i == _playerIndex)
            DrawText(">>", _hudPadding + _hudPos.first, y + 3 + _hudPos.second + _hudPadding, _textSize, RED);
        drawTextWrapped(
            "- " + std::to_string(player->getPlayerNumber()) + " - " + player->getTeam()->getName(),
            _hudPadding + 30,
            y += 5,
            _hudWidth - _hudPadding * 2,
            _textSize,
            player->getTeam()->getColor(),
            false
        );
    }
}

void HudLeft::_drawPlayerInfos(Player *player, float &y)
{
    y += 10;
    drawTextWrapped(
        "--> Player " + std::to_string(player->getPlayerNumber()),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        player->getTeam()->getColor(),
        false
    );
    drawTextWrapped(
        "Level: " + std::to_string(player->getLevel()),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
    drawTextWrapped(
        "Position: " + std::to_string(player->getPosition().first) + "x" + std::to_string(player->getPosition().second),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
    drawTextWrapped(
        "Orientation: " + orientationToString(player->getOrientation()),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
    drawTextWrapped(
        "Inventory:",
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
    for (const auto &item : player->getInventory()) {
        std::string resourceName = typeToString(item.first);
        int quantity = item.second;
        drawTextWrapped(
            "- " + resourceName + ": " + std::to_string(quantity),
            _hudPadding + 30,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            BLACK,
            false
        );
    }
}
