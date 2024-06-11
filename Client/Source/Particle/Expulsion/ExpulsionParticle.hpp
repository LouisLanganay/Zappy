/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Expulsion
*/

#ifndef EXPULSION_HPP_
#define EXPULSION_HPP_

#include "../AParticle.hpp"
#include <raylib.h>

namespace Zappy {
#include <vector>
#include "raylib.h"
#include <cmath>

        class ExpulsionParticle : public AParticle {
            public:
                ExpulsionParticle(float x, float y, float z, float vx, float vy, float vz, float lifetime)
                : AParticle(x, y, z, vx, vy, vz, lifetime)
                {
                    int numSpheres = 15;
                    for (int i = 0; i < numSpheres; ++i)
                        spheres.push_back({x, y, z});
                }

            void update(float deltaTime) override
            {
                float slowFactor = 0.005f;
                for (auto& sphere : spheres) {
                    sphere.x += _vx * deltaTime * slowFactor;
                    sphere.y += _vy * deltaTime * slowFactor;
                    sphere.z += _vz * deltaTime * slowFactor;
                }
                _lifetime -= deltaTime;
            }

            void draw() const override
            {
                float alpha = _lifetime / _initialLifetime;
                float randomFactor = GetRandomValue(-20, 20) / 100.0f;

                Color color = {
                    (unsigned char)(128 + (randomFactor * 128)),
                    (unsigned char)(128 + (randomFactor * 128)),
                    (unsigned char)(128 + (randomFactor * 128)),
                    (unsigned char)(alpha * 255)
                };
                for (const auto& sphere : spheres)
                    DrawSphere({ sphere.x, sphere.y, sphere.z }, 0.08f, color);
            }

        private:
            struct Sphere {
                float x, y, z;
            };

            std::vector<Sphere> spheres;
        };
}

#endif /* !EXPULSION_HPP_ */
