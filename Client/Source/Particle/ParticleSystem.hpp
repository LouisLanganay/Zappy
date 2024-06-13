/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ParticleSystem
*/

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

#include <vector>
#include <memory>
#include <math.h>
#include <algorithm>

#include "IParticle.hpp"
#include "Expulsion/ExpulsionParticle.hpp"
#include "Expulsion/IncantationParticle.hpp"

namespace Zappy {
    class ParticleSystem {
        public:
            void emit(ParticleType type, float x, float y, float z, int count)
            {
                for (int i = 0; i < count; ++i) {
                    float angleXY = (float)GetRandomValue(0, 360) * DEG2RAD;
                    float angleZ = (float)GetRandomValue(0, 360) * DEG2RAD;
                    float speed = (float)GetRandomValue(50, 100) / 10.0f;
                    float vx = cosf(angleXY) * speed;
                    float vy = sinf(angleXY) * speed;
                    float vz = sinf(angleZ) * speed;
                    float lifetime = (float)GetRandomValue(50, 100) / 10.0f;

                    if (type == ParticleType::EXPULSION)
                        _particles.emplace_back(std::make_unique<ExpulsionParticle>(x, y, z, vx, vy, vz, lifetime));
                    if (type == ParticleType::INCANTATION)
                        _particles.emplace_back(std::make_unique<IncantationParticle>(x, y, z, vx, vy, vz, lifetime));
                }
            }

            void update(float deltaTime)
            {
                for (auto& particle : _particles)
                    particle->update(deltaTime);
                _particles.erase(
                    std::remove_if(_particles.begin(), _particles.end(), [](const std::unique_ptr<IParticle>& p) { return !p->isAlive(); }),
                    _particles.end()
                );
            }

            void draw() const
            {
                for (const auto& particle : _particles)
                    particle->draw();
            }

        private:
            std::vector<std::unique_ptr<IParticle>> _particles;
    };
}


#endif /* !PARTICLESYSTEM_HPP_ */
