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
                    int32_t color = _sprite[idx_0_sprite + i * _w + j];

                    if (color && 0x000000FF == 0x000000FF) // Check if the pixel is not transparent
                    {
                        p_background[idx_pixel] = color;
                    }
                    else if (color && 0x000000FF != 0x00000000) // Check if the pixel is transparent
                    {
                        int bg_color = p_background[idx_pixel];
                        int bg_r = (bg_color >> 24) & 0xFF;
                        int bg_g = (bg_color >> 16) & 0xFF;
                        int bg_b = (bg_color >> 8) & 0xFF;

                        int sp_r = (color >> 24) & 0xFF;
                        int sp_g = (color >> 16) & 0xFF;
                        int sp_b = (color >> 8) & 0xFF;
                        int sp_a = (color >> 0) & 0xFF;

                        int new_r = (bg_r * (255 - sp_a) + sp_r * sp_a) / 255;
                        int new_g = (bg_g * (255 - sp_a) + sp_g * sp_a) / 255;
                        int new_b = (bg_b * (255 - sp_a) + sp_b * sp_a) / 255;

                        p_background[idx_pixel] = (new_r << 24) | (new_g << 16) | (new_b << 8) | 0xFF;

                        std::cout << "Pixel color: " << std::hex << color
                                  << " Background color: " << std::hex << bg_color
                                  << " New color: " << std::hex << p_background[idx_pixel] << std::endl;
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