#include "GameEngine/Entity.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <cstring>

///////////////////////////////
// Entity
///////////////////////////////

Entity::Entity(const std::string &imagePath)
{
    LoadImage(imagePath);
}

Entity::Entity(const char *imagePath)
{
    LoadImage(imagePath);
}

Entity::~Entity()
{
    if (_sprite != nullptr)
    {
        delete[] _sprite;
        _sprite = nullptr;
    }
}

void Entity::LoadImage(const std::string &imagePath)
{
    int channels;
    unsigned char *data = stbi_load(imagePath.c_str(), &_w, &_h, &channels, STBI_rgb_alpha); // force RGBA

    if (!data)
    {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return;
    }

    _sprite = new int32_t[_w * _h];

    // Copy the data into our buffer
    memcpy(_sprite, data, _w * _h * sizeof(int32_t));

    std::cout << "Loaded image: " << imagePath
              << " with size: " << _w << "x" << _h << std::endl;

    // Free the original image
    stbi_image_free(data);
}

void Entity::SetPosition(int x, int y)
{
    _x = x;
    _y = y;
}
void Entity::SetX(int x)
{
    _x = x;
}
void Entity::SetY(int y)
{
    _y = y;
}

void Entity::IncrementX(int x)
{
    _x += x;
}
void Entity::IncrementY(int y)
{
    _y += y;
}

int Entity::GetWidth() const
{
    return _w;
}
int Entity::GetHeight() const
{
    return _h;
}

void Entity::SetPixel(size_t idxPixel, int32_t color)
{
    if (idxPixel >= 0 && idxPixel < _w * _h)
    {
        _sprite[idxPixel] = color;
    }
}

///////////////////////////////
// Background
///////////////////////////////
/**
 * @brief Draws the entity on the background.
 *
 * This function draws the entity on the background by copying the entity's sprite
 * pixels to the background array. The position of the entity is taken into account
 * to determine where to place the pixels in the background.
 *
 * @param entity The entity to draw on the background.
 */
void Background::Draw(const Entity &entity)
{
    if (_background != nullptr && _sprite != nullptr)
    {
        for (int i = 0; i < entity._h; i++)
        {
            for (int j = 0; j < entity._w; j++)
            {
                int idx_pixel = (i + entity._y) * _w + (j + entity._x);
                if (idx_pixel >= 0 && idx_pixel < _w * _h)
                {
                    _background[idx_pixel] = entity._sprite[i * entity._w + j];
                }
            }
        }
    }
}

void Background::Clear()
{
    if (_sprite != nullptr)
    {
        if (_background != nullptr)
        {
            delete[] _background;
            _background = nullptr;
        }
        _background = new int32_t[_w * _h];
        memcpy(_background, _sprite, _w * _h * sizeof(int32_t));
    }
}

Background::~Background()
{
    if (_background != nullptr)
    {
        delete[] _background;
        _background = nullptr;
    }
}

const int32_t *Background::GetFrame() const
{
    return _background;
}