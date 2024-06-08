/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player
*/

#include "Player.hpp"
#include <queue>
#include <mutex>
#include "Debug.hpp"
#include "rlgl.h"
#include "../../Text/Text.hpp"

using namespace Zappy;

Player::Player(
    int playerNumber,
    std::unique_ptr<Team> team,
    Orientation orientation,
    int level
) : _playerNumber(playerNumber),
    _orientation(orientation),
    _team(std::move(team)),
    _level(level),
    _x(0),
    _y(0),
    _targetX(0),
    _targetY(0),
    _isMoving(false),
    _movementSpeed(1.0f),
    _timeAccumulator(0.0f)
{
    _inventory[Zappy::Resources::Type::FOOD] = 0;
    _inventory[Zappy::Resources::Type::LINEMATE] = 0;
    _inventory[Zappy::Resources::Type::DERAUMERE] = 0;
    _inventory[Zappy::Resources::Type::SIBUR] = 0;
    _inventory[Zappy::Resources::Type::MENDIANE] = 0;
    _inventory[Zappy::Resources::Type::PHIRAS] = 0;
    _inventory[Zappy::Resources::Type::THYSTAME] = 0;
}

int Player::getPlayerNumber() const
{
    return _playerNumber;
}

const Team* Player::getTeam() const
{
    return _team.get();
}

Orientation Player::getOrientation() const
{
    return _orientation;
}

int Player::getLevel() const
{
    return _level;
}

void Player::setOrientation(Orientation orientation)
{
    _orientation = orientation;
}

void Player::setLevel(int level)
{
    _level = level;
}

void Player::addResource(Zappy::Resources::Type type, int quantity)
{
    _inventory[type] += quantity;
}

void Player::setResource(Zappy::Resources::Type type, int quantity)
{
    _inventory[type] = quantity;
}

void Player::removeResource(Zappy::Resources::Type type, int quantity)
{
    if (_inventory[type] >= quantity)
        _inventory[type] -= quantity;
    else
        _inventory[type] = 0;
}

int Player::getResourceQuantity(const Zappy::Resources::IResources* resource) const
{
    auto it = _inventory.find(resource->getType());
    if (it != _inventory.end())
        return it->second;
    return 0;
}

void Player::setPosition(int x, int y)
{
    _targetX = x;
    _targetY = y;
    _isMoving = true;
    _timeAccumulator = 0.0f;
}

void Player::update(float deltaTime)
{
    if (!_isMoving)
        return;

    float distance = std::sqrt((_targetX - _x) * (_targetX - _x) + (_targetY - _y) * (_targetY - _y));
    float duration = distance / _movementSpeed;
    _timeAccumulator += deltaTime;

    if (_timeAccumulator >= duration) {
        _x = _targetX;
        _y = _targetY;
        _isMoving = false;
        _timeAccumulator = 0.0f;
    } else {
        float t = _timeAccumulator / duration;
        _x = _x + t * (_targetX - _x);
        _y = _y + t * (_targetY - _y);
    }
}

std::pair<int, int> Player::getPosition() const
{
    return {_x, _y};
}

void Player::addBroadcast(const std::string& message)
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    _broadcasts.push({message, std::chrono::steady_clock::now()});
    DEBUG_SUCCESS("Player " + std::to_string(_playerNumber) + " broadcasted: " + message);
}

std::string Player::getBroadcast()
{
    auto now = std::chrono::steady_clock::now();
    if (_broadcasts.empty())
        return "";

    if (_lastBroadcastTime == std::chrono::time_point<std::chrono::steady_clock>{}) {
        _lastBroadcastTime = now;
        return _broadcasts.front().message;
    }

    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - _lastBroadcastTime).count();
    int displayTime = 5 + _broadcasts.front().message.size() / 10;

    if (elapsedSeconds >= displayTime) {
        _lastBroadcastTime = now;
        _broadcasts.pop();
        if (_broadcasts.empty())
            return "";
    }
    return _broadcasts.front().message;
}

void Player::draw(Camera camera)
{
    Vector3 position = {_x, 0.5f, _y};

    DrawCube(position, 0.5f, 0.5f, 0.5f, _team->getColor());
    DrawCubeWires(position, 0.5f, 0.5f, 0.5f, BLACK);

    Vector3 spherePosition = position;
    if (_orientation == Orientation::NORTH)
        spherePosition.z -= 0.2f;
    else if (_orientation == Orientation::SOUTH)
        spherePosition.z += 0.2f;
    else if (_orientation == Orientation::EAST)
        spherePosition.x += 0.2f;
    else if (_orientation == Orientation::WEST)
        spherePosition.x -= 0.2f;

    spherePosition.y += 0.2f;

    DrawSphere(spherePosition, 0.2f, BLACK);

    if (!_isSelected)
        return;

    const char* opt = "Selected player";
    WaveTextConfig wcfg;
    wcfg.waveSpeed.x = wcfg.waveSpeed.y = 3.0f; wcfg.waveSpeed.z = 0.5f;
    wcfg.waveOffset.x = wcfg.waveOffset.y = wcfg.waveOffset.z = 0.35f;
    wcfg.waveRange.x = wcfg.waveRange.y = wcfg.waveRange.z = 0.45f;

    Text text;
    Vector3 tbox = text.MeasureTextWave3D(GetFontDefault(), opt, 3, 1, 1);
    Vector3 pos = {position.x - tbox.x / 2, position.y + 1.0f, position.z - tbox.z / 2};
    text.DrawTextWave3D(GetFontDefault(), opt, pos, 3, 1, 1, true, &wcfg, GetTime(), BLACK);
}

std::unordered_map<Zappy::Resources::Type, int> Player::getInventory() const
{
    return _inventory;
}

void Player::layEgg()
{
    DEBUG_SUCCESS("Player " + std::to_string(_playerNumber) + " laid an egg");
    // TODO: Implement laying egg animation
}

void Player::setSelected(bool selected)
{
    _isSelected = selected;
}

bool Player::isSelected() const
{
    return _isSelected;
}

void Player::startIncantation()
{

}

void Player::endIncantation(int result)
{

}
