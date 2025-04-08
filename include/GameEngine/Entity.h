#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>

class Entity
{
public:
    Entity(const std::string &imagePath);
    Entity(const char *imagePath);
    ~Entity();

    void LoadImage(const std::string &imagePath);

    void SetPosition(int x, int y);
    void SetX(int x);
    void SetY(int y);
    void IncrementX(int x);
    void IncrementY(int y);

    int GetWidth() const;
    int GetHeight() const;

    void SetPixel(size_t idxPixel, int32_t color);

protected:
    int _id{-1};
    int _x{0};
    int _y{0};
    int _w{0};
    int _h{0};

    int32_t *_sprite{nullptr};

    friend class Background;
};

class Background : public Entity
{

public:
    Background(const std::string &imagePath) : Entity(imagePath) {};
    Background(const char *imagePath) : Entity(imagePath) {};
    void Draw(const Entity &entity);
    void Clear();

    ~Background();

    int32_t *GetFrame();

private:
    int32_t *_background{nullptr};
};

class Spritesheet : public Entity
{
public:
    Spritesheet(const std::string &imagePath, int num_rows, int num_cols);

    Spritesheet(const char *imagePath, int num_rows, int num_cols);

    //~Spritesheet();

    void DrawSprite(int row, int col, Background &background);

private:
    int _num_rows{0};
    int _num_cols{0};

    int _sprite_width{0};
    int _sprite_height{0};
};

#endif // __ENTITY_H__
