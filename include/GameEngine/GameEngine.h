#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

struct SDL_Window;
typedef void *SDL_GLContext;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void Run();

private:
    void Init();

    void DrawCircle();

    bool _running{false};
    const int _w_width{800};
    const int _w_height{600};

    // Coordenades del cercle
    float _x_circle{0.0f};
    float _y_circle{0.0f};
    const float _radius{0.1f};
    const float _speed{0.01f};
    int _num_segments{100};

    SDL_Window *_window{nullptr};
    SDL_GLContext _gl_context{nullptr};
};

#endif // __GAME_ENGINE_H__