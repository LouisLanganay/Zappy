/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AParticle
*/

#ifndef APARTICLE_HPP_
#define APARTICLE_HPP_

#include "IParticle.hpp"

namespace Zappy {
    class AParticle : public IParticle {
        public:
            AParticle(
                float x,
                float y,
                float z,
                float vx,
                float vy,
                float vz,
                float lifetime
            ) : _x(x),
                _y(y),
                _z(z),
                _vx(vx),
                _vy(vy),
                _vz(vz),
                _lifetime(lifetime),
                _initialLifetime(lifetime)
            {
            }

            void update(float deltaTime) override
            {
                _x += _vx * deltaTime;
                _y += _vy * deltaTime;
                _z += _vz * deltaTime;
                _lifetime -= deltaTime;
            }

            bool isAlive() const override
            {
                return _lifetime > 0;
            }

        protected:
            float _x, _y, _z;
            float _vx, _vy, _vz;
            float _lifetime;
            float _initialLifetime;
    };
}

#endif /* !APARTICLE_HPP_ */
