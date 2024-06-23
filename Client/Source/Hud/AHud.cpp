/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AHud
*/

#include "AHud.hpp"
#include "Debug.hpp"

#include "Exceptions.hpp"

using namespace Zappy;

AHud::AHud(std::pair<float, float> hudRes, std::pair<float, float> hudPos)
{
    _hudWidth = hudRes.first;
    _hudHeight = hudRes.second;
    _hudPos = hudPos;
}

void AHud::loadFonts()
{
    _titleFont = LoadFontEx("Client/Fonts/Mario-Kart-DS.ttf", _titleSize, NULL, 0);
    _textFont = LoadFontEx("Client/Fonts/Minecraft.ttf", _textSize, NULL, 0);
    if (_titleFont.texture.id == 0)
        throw Zappy::GraphicException("Failed to load font \"Mario-Kart-DS.ttf\"");
    if (_textFont.texture.id == 0)
        throw Zappy::GraphicException("Failed to load font \"Minecraft.ttf\"");
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
}

void AHud::drawTextWrapped(
    const std::string &text,
    float x,
    float &y,
    float maxWidth,
    float fontSize,
    const Color &color,
    bool underline,
    Font font
)
{
    std::vector<std::string> lines;
    std::string line;
    std::istringstream iss(text);

    for (std::string word; iss >> word;) {
        if (MeasureTextEx(font, (line + word).c_str(), fontSize, 1).x > maxWidth) {
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
        DrawTextEx(font, l.c_str(), {x + _hudPos.first + _hudPadding, y + _hudPos.second + _hudPadding}, fontSize, 1, color);
        y += fontSize;
    }
    if (lines.size() > 1)
        y += 10;
    if (underline)
        DrawLine(
            x + _hudPos.first + _hudPadding,
            y + _hudPos.second + _hudPadding,
            x + MeasureTextEx(font, lines.back().c_str(), fontSize, 1).x + _hudPos.first + _hudPadding,
            y + _hudPos.second + _hudPadding,
            color
        );
}

void AHud::drawSectionTitle(
    const std::string &title,
    float &y,
    const Color &color
)
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
        color,
        true,
        _titleFont
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

void AHud::setRatioSize(float ratio)
{
    _titleSize = 40.0f * ratio;
    _textSize = 35.0f * ratio;
}
