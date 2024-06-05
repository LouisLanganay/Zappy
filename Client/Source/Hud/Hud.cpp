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
    DrawRectangle(0, 0, _hudWidth, GetScreenHeight(), Fade(GRAY, 0.5f));

    drawServerInfos(map, y);
    drawTeams(map, y);
    drawResources(map, y);
}

void Hud::drawTextWrapped(
    const std::string &text,
    float x,
    float &y,
    float maxWidth,
    float fontSize,
    const Color &color
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
        RED
    );
}

void Hud::drawTeams(Map *map, float &y)
{
    drawSectionTitle("Teams:", y);
    for (auto &team : map->getTeams()) {
        drawTextWrapped(
            "- " + team->getName(),
            _hudPadding,
            y,
            _hudWidth - _hudPadding * 2,
            _textSize,
            team->getColor()
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
        WHITE
    );
    drawTextWrapped(
        "Map size: " + std::to_string(map->getWidth()) + "x" + std::to_string(map->getHeight()),
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        WHITE
    );
    drawTextWrapped(
        "Server messages:",
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        WHITE
    );
    std::string message = map->getServerMessage();
    if (message.empty()) message = "No message";
    drawTextWrapped(
        "- " + message,
        _hudPadding,
        y,
        _hudWidth - _hudPadding * 2,
        _textSize,
        WHITE
    );
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
            WHITE
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
