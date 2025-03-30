#include "graphics/NcursesGraphics.h"

#include <ncurses.h>
#include <format>


void Display::SetMarginColor(FontColor color)
{
    _margin_color = color;
}


void Display::DrawText(const std::string& text, 
                     int x, 
                     int y, 
                     FontColor color, 
                     int fontFlags)
{
    attron(COLOR_PAIR(color) | fontFlags);
    mvprintw(y, x, text.c_str());
    attroff(COLOR_PAIR(color) | fontFlags);
}


void Display::Init()
{
    initscr();
    noecho();
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    if (has_colors()) {
        InitColorPalettes();
    }
}


int Display::GetChar()
{
    return getch();
}


void Display::NewFrame()
{
    erase();

    if(_margin_color)
    {
        DrawScreenMargins();
    }
    //drawLines();
    
}
void Display::Refresh()
{
    refresh();
}

Display::~Display()
{
    endwin();
}

int Display::NumLines()
{
    return LINES;
}

int Display::NumColumns()
{
    return COLS;
}

void Display::InitColorPalettes() 
{
    start_color();

    init_pair(static_cast<short>(FontColor::RED_OVER_BLACK), 
              COLOR_RED, 
              COLOR_BLACK);
            
    init_pair(static_cast<short>(FontColor::GREEN_OVER_BLACK),
              COLOR_GREEN, 
              COLOR_BLACK);

    init_pair(static_cast<short>(FontColor::YELLOW_OVER_BLACK), 
              COLOR_YELLOW, 
              COLOR_BLACK);

    init_pair(static_cast<short>(FontColor::BLUE_OVER_BLACK), 
              COLOR_BLUE, 
              COLOR_BLACK);

    init_pair(static_cast<short>(FontColor::MAGENTA_OVER_BLACK), 
              COLOR_MAGENTA, 
              COLOR_BLACK);

    init_pair(static_cast<short>(FontColor::CYAN_OVER_BLACK), 
              COLOR_CYAN, 
              COLOR_BLACK);

    init_pair(static_cast<short>(FontColor::RED_OVER_BLACK), 
              COLOR_WHITE, 
              COLOR_BLACK);


    init_pair(static_cast<short>(FontColor::BLACK_OVER_RED),
                COLOR_BLACK, 
                COLOR_RED);
    
    init_pair(static_cast<short>(FontColor::GREEN_OVER_RED),
                COLOR_GREEN, 
                COLOR_RED);

    init_pair(static_cast<short>(FontColor::YELLOW_OVER_RED),
                COLOR_YELLOW, 
                COLOR_RED);
    
    init_pair(static_cast<short>(FontColor::BLUE_OVER_RED),
                COLOR_BLUE, 
                COLOR_RED);

    init_pair(static_cast<short>(FontColor::MAGENTA_OVER_RED),
                COLOR_MAGENTA, 
                COLOR_RED);
            
    init_pair(static_cast<short>(FontColor::CYAN_OVER_RED),
                COLOR_CYAN, 
                COLOR_RED); 
            
    init_pair(static_cast<short>(FontColor::WHITE_OVER_RED),
                COLOR_WHITE, 
                COLOR_RED);

    init_pair(static_cast<short>(FontColor::BLACK_OVER_GREEN),
                COLOR_BLACK, 
                COLOR_GREEN);

}


void Display::DrawScreenMargins(FontColor color, 
                                unsigned int horitzontalChar, 
                                unsigned int verticalChar) 
{
    attron(COLOR_PAIR(color));
    box(stdscr, verticalChar, horitzontalChar);
    attroff(COLOR_PAIR(color));
}




TextSprite::TextSprite(const std::vector<std::vector<char>>& sprite, 
                       FontColor color)
{
    _sprite = sprite;
    _color = color;
}

TextSprite::TextSprite(const std::vector<std::vector<char>>& sprite)
{
    _sprite = sprite;
}

TextSprite::TextSprite()
{

}


void TextSprite::SetPos(int x, int y)
{
    if(x > 0 && x < COLS - _sprite[0].size())
    {
        _x = x;
    }
    if(y > 0 && y < LINES - _sprite.size())
    {
        _y = y;
    }
}

void TextSprite::Draw(Display& display)
{
    for (size_t num_col = 0; num_col < _sprite.size(); num_col++) 
    {
        for (size_t num_row = 0; num_row < _sprite[num_col].size(); num_row++) 
        {
            if (_sprite[num_col][num_row] != ' ') 
            {
                display.DrawText(std::string(1, _sprite[num_col][num_row]), 
                                 _x + num_row, 
                                 _y + num_col, 
                                 _color);
            }
        }
    }
}