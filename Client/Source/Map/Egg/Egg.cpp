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
    _drawPosition.x = GetRandomValue(-30, 30) / 100.0f;
    _drawPosition.y = GetRandomValue(-30, 30) / 100.0f;
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

void Egg::draw(Model3D model, float height)
{
    if (_hatched)
        return;

    Vector3 position = {(float)_position.first + _drawPosition.x, height + 0.2f, (float)_position.second + _drawPosition.y};
    float scale = 0.05f;

    if (_isHatching) {
        float progress = (float)_animationFrame / (float)_animationFrameMax;
        scale += progress * 0.05f;

        if (_animationFrame >= _animationFrameMax) {
            _isHatching = false;
            _hatched = true;
        }
    }

    Vector3 topSpherePosition = {position.x, position.y + scale * 0.5f, position.z};
    Vector3 bottomSpherePosition = {position.x, position.y - scale * 0.5f, position.z};
    DrawSphere(topSpherePosition, scale, _team->getColor());
    DrawSphere(bottomSpherePosition, scale * 1.5, _team->getColor());
    DrawSphereWires(topSpherePosition, scale, 16, 16, BLACK);
    DrawSphereWires(bottomSpherePosition, scale * 1.5, 16, 16, BLACK);
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
