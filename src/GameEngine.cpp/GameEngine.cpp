#include "GameEngine/GameEngine.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <cmath>

GameEngine::GameEngine()
{
    // Constructor
    Init();
}
GameEngine::~GameEngine()
{
    // Destructor
    SDL_GL_DeleteContext(_gl_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void GameEngine::Run()
{
    SDL_Event event;

    int32_t image[_w_width * _w_height];
    int32_t frame[_w_width * _w_height];

    for (int idx_pixel = 0; idx_pixel < _w_width * _w_height; idx_pixel++)
    {
        //                 RGBA
        image[idx_pixel] = 0xFF0000FF;
    }

    int x_sprite = 0;
    int y_sprite = 0;
    int speed_sprite = 1;

    int w_sprite = 40;
    int h_sprite = 80;
    int32_t sprite[w_sprite * h_sprite];

    for (int idx_pixel = 0; idx_pixel < w_sprite * h_sprite; idx_pixel++)
    {
        //                 RGBA
        sprite[idx_pixel] = 0x00FFFFFF;
    }

    while (_running)
    {
        // entrada
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                _running = false;
            }
        }

        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT])
        {
            _x_circle -= _speed;
            x_sprite -= speed_sprite;
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            _x_circle += _speed;
            x_sprite += speed_sprite;
        }
        if (keys[SDL_SCANCODE_UP])
        {
            _y_circle += _speed;
            y_sprite += speed_sprite;
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            _y_circle -= _speed;
            y_sprite -= speed_sprite;
        }
        if (keys[SDL_SCANCODE_ESCAPE])
        {
            _running = false;
        }

        // render
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*
        // configura coordenades de dibuix (-1 a 1)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1, 1, -1, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        DrawCircle();
        */
        // glRasterPos2f(-1.0f, -1.0f);

        memcpy(frame, image, _w_height * _w_width * sizeof(int32_t));

        for (int i = 0; i < h_sprite; i++)
        {
            for (int j = 0; j < w_sprite; j++)
            {
                int idx_pixel = (i + y_sprite) * _w_width + (j + x_sprite);
                if (idx_pixel >= 0 && idx_pixel < _w_width * _w_height)
                {
                    frame[idx_pixel] = sprite[i * w_sprite + j];
                }
            }
        }

        glDrawPixels(_w_width, _w_height, GL_RGBA, GL_UNSIGNED_BYTE, frame);

        SDL_GL_SwapWindow(_window);
    }
}

void GameEngine::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow(_window_title.c_str(),
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _w_width, _w_height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    _gl_context = SDL_GL_CreateContext(_window);
    SDL_GL_SetSwapInterval(1); // VSYNC
    _running = true;
}

void GameEngine::DrawCircle()
{

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.8f, 0.2f, 0.3f);      // color del cercle
    glVertex2f(_x_circle, _y_circle); // centre
    for (int i = 0; i <= _num_segments; i++)
    {
        float angle = 2.0f * M_PI * i / _num_segments;
        float x = _radius * cosf(angle);
        float y = _radius * sinf(angle);
        glVertex2f(_x_circle + x, _y_circle + y);
    }
    glEnd();
}