#include "GameEngine/GameEngine.h"

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
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            _x_circle += _speed;
        }
        if (keys[SDL_SCANCODE_UP])
        {
            _y_circle += _speed;
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            _y_circle -= _speed;
        }
        if (keys[SDL_SCANCODE_ESCAPE])
        {
            _running = false;
        }

        // render
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // configura coordenades de dibuix (-1 a 1)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1, 1, -1, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        DrawCircle();

        SDL_GL_SwapWindow(_window);
    }
}

void GameEngine::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow("Cercle amb SDL2 + OpenGL",
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