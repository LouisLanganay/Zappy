/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IncantationParticle
*/

#ifndef INCANTATIONPARTICLE_HPP_
#define INCANTATIONPARTICLE_HPP_

#include "../AParticle.hpp"
#include <vector>
#include <raylib.h>
#include <cmath>

namespace Zappy {

    class IncantationParticle : public AParticle {
    public:
        IncantationParticle(float x, float y, float z, float vx, float vy, float vz, float lifetime)
            : AParticle(x, y, z, vx, vy, vz, lifetime)
        {
            int numParticles = 10;
            for (int i = 0; i < numParticles; ++i) {
                float offsetAngleXY = (float)GetRandomValue(0, 360) * DEG2RAD;
                float offsetDistance = (float)GetRandomValue(1, 5) / 10.0f;
                particles.push_back({x + cosf(offsetAngleXY) * offsetDistance, y, z + sinf(offsetAngleXY) * offsetDistance});
            }
        }

        void update(float deltaTime) override {
            float slowFactor = 0.002f;
            for (auto& particle : particles) {
                particle.x += _vx * deltaTime * slowFactor;
                particle.y += _vy * deltaTime * slowFactor;
                particle.z += _vz * deltaTime * slowFactor;
            }
            _lifetime -= deltaTime;
        }

        void draw() const override {
            float alpha = _lifetime / _initialLifetime;
            for (const auto& particle : particles) {
                Color color = {
                    (unsigned char)(GetRandomValue(150, 255)),
                    (unsigned char)(GetRandomValue(100, 255)),
                    (unsigned char)(GetRandomValue(150, 255)),
                    (unsigned char)(alpha * 255)
                };
                DrawSphere({ particle.x, particle.y, particle.z }, 0.05f, color);
            }
        }

    private:
        struct Particle {
            float x, y, z;
        };

        std::vector<Particle> particles;
    };
}

#endif /* !INCANTATIONPARTICLE_HPP_ */
