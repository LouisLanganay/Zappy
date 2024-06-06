/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Hud
*/

#include "Hud.hpp"

using namespace Zappy;

Hud::Hud()
{
}

void Hud::draw(Map *map)
{
    float y = 50;
    DrawRectangle(0, 0, _hudWidth, GetScreenHeight(), Fade(SKYBLUE, 0.2f));
    DrawRectangleLines(0, 0, _hudWidth, GetScreenHeight(), BLUE);

    drawTeams(map, y);
    drawServerInfos(map, y);
    drawPlayers(map, y);
    if (_selectedPlayer != -1)
        drawPlayerInfos(map->getPlayer(_selectedPlayer), y);
    drawResources(map, y);
}

void Hud::drawTextWrapped(
    const std::string &text,
    float x,
    float &y,
    float maxWidth,
    float fontSize,
    const Color &color,
    bool underline
)
{
    std::vector<std::string> lines;
    std::string line;
    std::istringstream iss(text);
    for (std::string word; iss >> word;) {
        if (MeasureTextEx(GetFontDefault(), (line + word).c_str(), fontSize, 1).x > maxWidth) {
            if (word.size() > maxWidth / fontSize) {
                int parts = word.size() / (maxWidth / fontSize) + 1;
                int partSize = word.size() / parts;
                for (int i = 0; i < parts; ++i) {
                    std::string subword = word.substr(i * partSize, partSize);
                    if (i != parts - 1) subword += "-";
                    lines.push_back(line);
                    line = subword + " ";
                }
            } else {
                lines.push_back(line);
                line = word + " ";
            }
        } else {
            line += word + " ";
        }
    }
    lines.push_back(line);

    for (auto &line : lines) {
        DrawTextEx(
            GetFontDefault(),
            line.c_str(),
            {x, y},
            fontSize,
            2,
            color
        );
        if (underline) {
            DrawRectangle(
                x,
                y + fontSize - 2,
                MeasureTextEx(GetFontDefault(), line.c_str(), fontSize, 1).x,
                3,
                color
            );
        }
        y += fontSize;
    }
}

void Hud::drawSectionTitle(const std::string &title, float &y)
{
    y += _titleSize;
    drawTextWrapped(
        title,
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _titleSize,
        RED,
        true
    );
    y += 10;
}

void Hud::drawTeams(Map *map, float &y)
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

void Hud::drawServerInfos(Map *map, float &y)
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
        "Map size: " + std::to_string(map->getWidth()) + "x" + std::to_string(map->getHeight()),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
    drawTextWrapped(
        "Server messages:",
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        BLACK,
        false
    );
    std::string message = map->getServerMessage();
    if (!message.empty()) {
        drawTextWrapped(
            "- " + message,
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            BLACK,
            false
        );
    } else {
        drawTextWrapped(
            "- No message",
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            BLACK,
            false
        );
    }
}

void Hud::drawResources(Map *map, float &y)
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
}

void Hud::drawPlayers(Map *map, float &y) {
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
        if (players[_playerIndex]->getPlayerNumber() != _selectedPlayer)
            _selectedPlayer = players[_playerIndex]->getPlayerNumber();
        else
            _selectedPlayer = -1;
    }

    for (size_t i = 0; i < players.size(); ++i) {
        const auto &player = players[i];
        if (player->getPlayerNumber() == _selectedPlayer) {
            Color color = player->getTeam()->getColor();
            DrawRectangle(
                _hudPadding - 5,
                y - 3,
                _hudWidth - _hudPadding * 2,
                _textSize + 10,
                Fade(color, 0.2f)
            );
        }
        if (i == _playerIndex)
            DrawText(">>", _hudPadding, y + 3, _textSize, RED);
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

void Hud::drawPlayerInfos(Player *player, float &y)
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

std::string Hud::typeToString(Resources::Type type)
{
    switch(type) {
        case Resources::Type::FOOD:
            return "FOOD";
        case Resources::Type::LINEMATE:
            return "LINEMATE";
        case Resources::Type::DERAUMERE:
            return "DERAUMERE";
        case Resources::Type::SIBUR:
            return "SIBUR";
        case Resources::Type::MENDIANE:
            return "MENDIANE";
        case Resources::Type::PHIRAS:
            return "PHIRAS";
        case Resources::Type::THYSTAME:
            return "THYSTAME";
    }
    return "";
}

std::string Hud::orientationToString(Orientation orientation)
{
    switch(orientation) {
        case Orientation::NORTH:
            return "NORTH";
        case Orientation::EAST:
            return "EAST";
        case Orientation::SOUTH:
            return "SOUTH";
        case Orientation::WEST:
            return "WEST";
    }
    return "";
}
