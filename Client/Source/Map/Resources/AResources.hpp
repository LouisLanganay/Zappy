/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AResources
*/

#ifndef ARESOURCES_HPP_
#define ARESOURCES_HPP_

#include <unordered_map>

#include "../../Model3D/Model3D.hpp"
#include "IResources.hpp"

namespace Zappy::Resources {
    class AResources : public IResources {
        public:
            AResources(const std::string& type, int initialQuantity = 0);
            AResources(Type type, int initialQuantity = 0);
            virtual ~AResources() = default;

            Type getType() const override;
            int getQuantity() const override;
            void setQuantity(int quantity) override;
            void addQuantity(int quantity) override;
            void removeQuantity(int quantity) override;

        protected:
            Type type;
            int quantity;
        private:
    };
}

#endif /* !ARESOURCES_HPP_ */
