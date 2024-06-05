/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IResources
*/

#ifndef IRESOURCES_HPP
#define IRESOURCES_HPP

#include <string>

namespace Zappy::Resources {
    enum class Type {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };
    class IResources {
        public:
            virtual ~IResources() = default;

            virtual Type getType() const = 0;
            virtual int getQuantity() const = 0;
            virtual void setQuantity(int quantity) = 0;
            virtual void addQuantity(int quantity) = 0;
            virtual void removeQuantity(int quantity) = 0;

        protected:
        private:
    };
}

#endif // IRESOURCES_HPP
