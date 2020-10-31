#include "Graphics.hpp"

class App
{
public:
    App(ImGuiIO &io);
    void Quit();
    void NewFrame();
    void Render();

    SDL_WindowFlags window_flags;
    SDL_Window *window;
    SDL_GLContext gl_context;
    ImVec4 clear_color;
    ImGuiIO &io;

private:
};