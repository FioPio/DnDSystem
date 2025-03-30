/*********************************************
 * 
 */
#ifndef __NCURSES_GRAPHICS_H__
#define __NCURSES_GRAPHICS_H__
#include <optional>
#include <string>
#include <vector>



enum class FontColor
{
    RED_OVER_BLACK = 1,
    GREEN_OVER_BLACK = 2,
    YELLOW_OVER_BLACK = 3,
    BLUE_OVER_BLACK = 4,
    MAGENTA_OVER_BLACK = 5,
    CYAN_OVER_BLACK = 6,
    WHITE_OVER_BLACK = 7,

    BLACK_OVER_RED = 8,
    GREEN_OVER_RED = 9,
    YELLOW_OVER_RED = 10,
    BLUE_OVER_RED = 11,
    MAGENTA_OVER_RED = 12,
    CYAN_OVER_RED = 13,
    WHITE_OVER_RED = 14,

    BLACK_OVER_GREEN = 15,

};

enum class Key
{
    DOWN = 0402,
    UP = 0403,
    LEFT = 0404,
    RIGHT = 0405,
};

// Singleton that allows for screen management
class Display
{
public:
    
    //Display();
    ~Display();

    void SetMarginColor(FontColor color);

        /*// Do not allow copies
        Display(const Display&) = delete;
        // Do not allow assignations
        Display& operator = (const Display&) = delete;*/

    void DrawText(const std::string& text, 
                  int x, 
                  int y, 
                  FontColor color, 
                  int fontFlags = 0);

    void Init();

    int GetChar();

    void NewFrame();

    void Refresh();

    int NumLines();

    int NumColumns();

private:

    void InitColorPalettes();

    void DrawScreenMargins(FontColor color = FontColor::BLUE_OVER_BLACK,
                           unsigned int horitzontalChar=0, 
                           unsigned int verticalChar=0);

    std::optional<FontColor> _margin_color {std::nullopt};
};


class TextSprite
{
public:
    TextSprite(const std::vector<std::vector<char>>& sprite, FontColor color);

    TextSprite(const std::vector<std::vector<char>>& sprite);

    TextSprite();

    void SetPos(int x, int y);

    void Draw(Display& display);

private:
    int _x {0};
    int _y {0};
    std::vector<std::vector<char>> _sprite {{}};
    FontColor _color {FontColor::RED_OVER_BLACK};

};

#endif // __NCURSES_GRAPHICS_H__