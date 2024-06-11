/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"
#include "Debug.hpp"

using namespace Zappy;

Egg::Egg(
    int eggNumber,
    int playerNumber,
    int x,
    int y,
    std::unique_ptr<Team> team
) : _eggNumber(eggNumber),
    _playerNumber(playerNumber),
    _position(x, y),
    _hatched(false),
    _team(std::move(team)),
    _isHatching(false),
    _animationFrame(0),
    _animationFrameMax(10),
    _frameTime(0.1f),
    _currentFrameTime(0.0f)
{
}


int Egg::getEggNumber() const
{
    return _eggNumber;
}

int Egg::getPlayerNumber() const
{
    return _playerNumber;
}

std::pair<int, int> Egg::getPosition() const
{
    return _position;
}

void Egg::setHatched(bool hatched)
{
    _hatched = hatched;
}

bool Egg::isHatched() const
{
    return _hatched;
}

void Egg::draw()
{
    if (_hatched)
        return;
    if (_isHatching) {
        // TODO: Hatching annimation
        _animationFrame++;
        if (_animationFrame > _animationFrameMax) {
            _isHatching = false;
            _hatched = true;
        }
    } else {
        Vector3 position = {(float)_position.first, 0.5f, (float)_position.second};
        DrawSphere(position, 0.35f, BROWN);
    }
}

const Team* Egg::getTeam() const
{
    return _team.get();
}

void Egg::startHatchingAnimation()
{
    _isHatching = true;
    _animationFrame = 0;
    _currentFrameTime = 0.0f;
}

void Egg::update(float deltaTime)
{
    if (!_isHatching)
        return;
    _currentFrameTime += deltaTime;
    if (_currentFrameTime >= _frameTime) {
        _animationFrame++;
        _currentFrameTime = 0.0f;
        if (_animationFrame > _animationFrameMax) {
            _isHatching = false;
            _hatched = true;
        }
    }
}
