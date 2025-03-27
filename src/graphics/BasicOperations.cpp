#include "graphics/BasicOperations.h"
#include <ncurses.h>
#include <chrono>
#include <thread>

using namespace std::chrono;

void initColors() {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

void drawBox() {
    attron(COLOR_PAIR(4));
    box(stdscr, 0, 0);
    attroff(COLOR_PAIR(4));
}

void drawLines() {
    attron(COLOR_PAIR(3));
    for (int i = 2; i < COLS - 2; i++) {
        mvprintw(5, i, "-");
        mvprintw(10, i, "=");
    }
    attroff(COLOR_PAIR(3));
}

void drawText(int x, int y, double fps) {
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(y, x, "Hello, ncurses!");
    attroff(COLOR_PAIR(2) | A_BOLD);

    attron(COLOR_PAIR(5) | A_UNDERLINE);
    mvprintw(y + 2, x, "Move with arrow keys!");
    attroff(COLOR_PAIR(5) | A_UNDERLINE);

    attron(COLOR_PAIR(1) | A_BLINK);
    mvprintw(y + 4, x, "Press 'q' to quit");
    attroff(COLOR_PAIR(1) | A_BLINK);

    // Display FPS
    attron(COLOR_PAIR(6) | A_BOLD);
    mvprintw(1, COLS - 15, "FPS: %.2f", fps);
    attroff(COLOR_PAIR(6) | A_BOLD);
}

int MainLoop() {
    initscr();
    noecho();
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    if (has_colors()) {
        initColors();
    }

    int x = 10, y = 5;
    int ch;
    int frameCount = 0;
    auto lastTime = high_resolution_clock::now();
    double fps = 0.0;

    while ((ch = getch()) != 'q') {
        erase();
        drawBox();
        drawLines();
        drawText(x, y, fps);

        switch (ch) {
            case KEY_UP:    y = (y > 1) ? y - 1 : y; break;
            case KEY_DOWN:  y = (y < LINES - 2) ? y + 1 : y; break;
            case KEY_LEFT:  x = (x > 1) ? x - 1 : x; break;
            case KEY_RIGHT: x = (x < COLS - 20) ? x + 1 : x; break;
        }

        refresh();
        frameCount++;

        // Calculate FPS every second
        auto currentTime = high_resolution_clock::now();
        double elapsedTime = duration<double>(currentTime - lastTime).count();
        if (elapsedTime >= 1.0) {
            fps = frameCount / elapsedTime;
            frameCount = 0;
            lastTime = currentTime;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Limit FPS (~60 FPS)
    }

    endwin();
    return 0;
}
