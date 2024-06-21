/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IParticle
*/

#ifndef IPARTICLE_HPP_
#define IPARTICLE_HPP_

namespace Zappy {
    enum class ParticleType {
        EXPULSION,
        INCANTATION
    };

    class IParticle {
        public:
            virtual ~IParticle() = default;
            virtual void update(float deltaTime) = 0;
            virtual void draw() const = 0;
            virtual bool isAlive() const = 0;
    };
}

#endif /* !IPARTICLE_HPP_ */
