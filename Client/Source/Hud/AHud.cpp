/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AHud
*/

#include "AHud.hpp"

using namespace Zappy;

AHud::AHud(std::pair<float, float> hudRes, std::pair<float, float> hudPos)
{
    _hudWidth = hudRes.first;
    _hudHeight = hudRes.second;
    _hudPos = hudPos;
}

void AHud::setHudWidth(float width)
{
    _hudWidth = width;
}

float AHud::getHudWidth()
{
    return _hudWidth;
}

void AHud::setHudHeight(float height)
{
    _hudHeight = height;
}

float AHud::getHudHeight()
{
    return _hudHeight;
}

void AHud::setHudPos(std::pair<float, float> pos)
{
    _hudPos = pos;
}

void AHud::draw(Map *map)
{
    _sectionMargin = false;
    DrawRectangle(
        _hudPos.first,
        _hudPos.second,
        _hudWidth == 0 ? GetScreenWidth() : _hudWidth,
        _hudHeight == 0 ? GetScreenHeight() : _hudHeight,
        Fade(SKYBLUE, 0.2f)
    );
    DrawRectangleLines(
        _hudPos.first,
        _hudPos.second,
        _hudWidth == 0 ? GetScreenWidth() : _hudWidth,
        _hudHeight == 0 ? GetScreenHeight() : _hudHeight,
        Fade(DARKBLUE, 0.6f)
    );
}

void AHud::drawTextWrapped(
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
    for (const auto &l : lines) {
        DrawTextEx(GetFontDefault(), l.c_str(), {x + _hudPos.first + _hudPadding, y + _hudPos.second + _hudPadding}, fontSize, 1, color);
        y += fontSize;
    }
    if (lines.size() > 1)
        y += 10;
    if (underline)
        DrawLine(
            x + _hudPos.first + _hudPadding,
            y + _hudPos.second + _hudPadding,
            x + MeasureTextEx(GetFontDefault(), lines.back().c_str(), fontSize, 1).x + _hudPos.first + _hudPadding,
            y + _hudPos.second + _hudPadding,
            color
        );
}

void AHud::drawSectionTitle(const std::string &title, float &y)
{
    if (_sectionMargin)
        y += _titleSize;
    _sectionMargin = true;
    drawTextWrapped(
        title,
        0,
        y,
        _hudWidth - _hudPadding * 2,
        _titleSize,
        RED,
        true
    );
    y += 10;
}

std::string AHud::typeToString(Resources::Type type)
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

std::string AHud::orientationToString(Orientation orientation)
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
