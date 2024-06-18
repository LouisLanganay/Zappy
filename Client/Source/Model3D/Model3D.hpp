/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Model3D
*/

#ifndef MODEL3D_HPP_
#define MODEL3D_HPP_

#include "raylib.h"
#include <iostream>

namespace Zappy {
    class Model3D {
        public:
            Model3D();
            Model3D(std::string model_path, std::string texture_path);
            Model3D(
                std::string model_path,
                std::string texture_path,
                float x,
                float y,
                float z
            );
            Model3D(
                std::string model_path,
                std::string texture_path,
                float x,
                float y,
                float z,
                float size
            );
            ~Model3D() {};

            void setSize(float size);
            void setPosition(float x, float y, float z);

            void draw();

            void unload();

            void setColor(Color color);
        protected:
            Model _model;
            Texture2D _texture;
            Vector3 _position;
            float _size;
    };
}

#endif /* !MODEL3D_HPP_ */
