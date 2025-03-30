#include <chrono>
#include <thread>

#include "graphics/NcursesGraphics.h"


namespace cr = std::chrono;

int main()
{
    Display display;
    /*
    "<(o_o)>"
    " -|_|-/"
    "  / \  "; 
     */
    TextSprite goblin (
        {{'<', '(', 'o', '_', 'o', ')', '>'},
         {' ', '-', '|', '_', '|', '-', '/'},
         {' ', ' ', '|', ' ', '|', ' ', ' '},
        },
        FontColor::BLACK_OVER_RED
    );

    TextSprite player (
        {{'#'}},
        FontColor::WHITE_OVER_RED

    );

    display.Init();

    int x = 10, y = 5;
    int ch;
    int frameCount = 0;
    auto lastTime = cr::high_resolution_clock::now();
    float fps = 0.0;

    display.SetMarginColor(FontColor::BLUE_OVER_BLACK);

    while ((ch = display.GetChar()) != 'q' && ch != 27) 
    {
        display.NewFrame();
        std::string fps_text = std::format("FPS: {:.2f}", fps);
        display.DrawText(fps_text,  
                 display.NumColumns() - 15, 
                 1,
                 FontColor::CYAN_OVER_BLACK);

        display.DrawText("Hello, ncurses!", 
                         10,
                         10,
                         FontColor::GREEN_OVER_BLACK);

        display.DrawText("Move with arrow keys!", 10, 12, FontColor::GREEN_OVER_BLACK);
        display.DrawText("Press 'q' to quit", 10, 14, FontColor::GREEN_OVER_BLACK);

        switch (ch) {
            case static_cast<int>(Key::UP): 
               y = (y > 1) ? y - 1 : y; 
               break;

            case static_cast<int>(Key::DOWN):  
                y = (y < display.NumLines() - 2) ? y + 1 : y; 
                break;

            case static_cast<int>(Key::LEFT):  
                x = (x > 1) ? x - 1 : x; 
                break;

            case static_cast<int>(Key::RIGHT): 
                x = (x < display.NumColumns() - 20) ? x + 1 : x; 
                break;
        }

        goblin.SetPos(x, y);
        player.SetPos(x + 10, y);
        goblin.Draw(display);
        player.Draw(display);

        display.Refresh();
        frameCount++;

        // Calculate FPS every second
        auto currentTime = cr::high_resolution_clock::now();
        double elapsedTime = cr::duration<double>(currentTime - lastTime).count();
        if (elapsedTime >= 1.0) {
            fps = frameCount / elapsedTime;
            frameCount = 0;
            lastTime = currentTime;
        }

        std::this_thread::sleep_for(cr::milliseconds(16)); // Limit FPS (~60 FPS)
    }
    
    return 0;
}
