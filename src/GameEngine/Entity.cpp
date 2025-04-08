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
    stbi_set_flip_vertically_on_load(1);                                                     // Flip the image vertically
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
              << " with size: " << _w << "x" << _h
              << " and channels: " << channels << std::endl;

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

int32_t *Background::GetFrame()
{
    return _background;
}

///////////////////////////////////////
// Spritesheet
///////////////////////////////////////
Spritesheet::Spritesheet(const std::string &imagePath, int num_rows, int num_cols)
    : Entity(imagePath)
{
    _num_rows = num_rows;
    _num_cols = num_cols;

    if (_sprite != nullptr)
    {
        int sprite_width = _w / num_cols;
        int sprite_height = _h / num_rows;

        std::cout << "Initialized fine" << std::endl;
    }
    else
    {
        std::cerr << "Sprite not loaded." << std::endl;
    }
}

Spritesheet::Spritesheet(const char *imagePath, int num_rows, int num_cols)
    : Entity(imagePath)
{
    _num_rows = num_rows;
    _num_cols = num_cols;

    if (_sprite != nullptr)
    {
        _sprite_width = _w / num_cols;
        _sprite_height = _h / num_rows;
    }
}

void Spritesheet::DrawSprite(int row, int col, Background &background)
{
    if (_sprite != nullptr)
    {
        row = _num_rows - row - 1; // Flip the sprite vertically
        int idx_0_sprite = row * _sprite_height * _w + col * _sprite_width;
        int idx_0_background = _y * background.GetWidth() + _x;

        int32_t *p_background = background.GetFrame();

        for (int i = 0; i < _sprite_height; i++)
        {
            for (int j = 0; j < _sprite_width; j++)
            {
                int idx_pixel = idx_0_background + (i + _y) * background.GetWidth() + (j + _x);
                if (idx_pixel >= 0 && idx_pixel < background.GetWidth() * background.GetHeight())
                {
                    PixelColor sprite_color = {_sprite[idx_0_sprite + i * _w + j]};

                    if (sprite_color.alpha == 0xFF) // Check if the pixel is not transparent
                    {
                        p_background[idx_pixel] = sprite_color.color;
                    }
                    else if (sprite_color.alpha != 0x00) // Check if the pixel is transparent
                    {
                        PixelColor bg_color = {p_background[idx_pixel]};

                        PixelColor new_color;

                        new_color.red = (bg_color.red * (255 - sprite_color.alpha) +
                                         sprite_color.red * sprite_color.alpha) /
                                        255;

                        new_color.green = (bg_color.green * (255 - sprite_color.alpha) +
                                           sprite_color.green * sprite_color.alpha) /
                                          255;

                        new_color.blue = (bg_color.blue * (255 - sprite_color.alpha) +
                                          sprite_color.blue * sprite_color.alpha) /
                                         255;

                        new_color.alpha = 0xFF;

                        p_background[idx_pixel] = sprite_color.color;
                    }
                }
                else
                {
                    std::cerr << "Index out of bounds: " << idx_pixel << std::endl;
                }
            }
        }
    }
    else
    {
        std::cerr << "Sprite not loaded." << std::endl;
    }
}