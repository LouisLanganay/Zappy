/*
** EPITECH PROJECT, 2024
** Model
** File description:
** Model
*/

#include "Model3D.hpp"
#include "Exceptions.hpp"

using namespace Zappy;

Model3D::Model3D()
{
}

Model3D::Model3D(std::string model_path, std::string texture_path)
{
    if (!FileExists(model_path.c_str()))
        throw ModelException("Model file not found: " + model_path);
    if (!FileExists(texture_path.c_str()))
        throw ModelException("Texture file not found: " + texture_path);

    _model = LoadModel(model_path.c_str());
    _texture = LoadTexture(texture_path.c_str());
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    _position = {0.0f, 0.0f, 0.0f};
    _size = 5;
}

Model3D::Model3D(std::string model_path)
{
    if (!FileExists(model_path.c_str()))
        throw ModelException("Model file not found: " + model_path);

    _model = LoadModel(model_path.c_str());
    _position = {0.0f, 0.0f, 0.0f};
    _size = 5;
}

Model3D::Model3D(
    std::string model_path,
    std::string texture_path,
    float x,
    float y,
    float z
)
{
    if (!FileExists(model_path.c_str()))
        throw ModelException("Model file not found: " + model_path);
    if (!FileExists(texture_path.c_str()))
        throw ModelException("Texture file not found: " + texture_path);

    _model = LoadModel(model_path.c_str());
    _texture = LoadTexture(texture_path.c_str());
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    _position = {x, y, z};
    _size = 5;
}

Model3D::Model3D(
    std::string model_path,
    std::string texture_path,
    float x,
    float y,
    float z,
    float size
)
{
    if (!FileExists(model_path.c_str()))
        throw ModelException("Model file not found: " + model_path);
    if (!FileExists(texture_path.c_str()))
        throw ModelException("Texture file not found: " + texture_path);

    _model = LoadModel(model_path.c_str());
    _texture = LoadTexture(texture_path.c_str());
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    _position = {x, y, z};
    _size = size;
}

void Model3D::setSize(float size)
{
    _size = size;
}

void Model3D::setPosition(float x, float y, float z)
{
    _position = {x, y, z};
}

void Model3D::draw()
{
    DrawModel(_model, _position, _size, WHITE);
}

void Model3D::unload()
{
    UnloadTexture(_texture);
    UnloadModel(_model);
}

void Model3D::setColor(Color color)
{
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = color;
}
