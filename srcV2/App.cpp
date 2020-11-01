#include "App.hpp"

App::App()
    : mWindow(nullptr), mIsRunning(true), mIo(nullptr)
{
}

bool App::Init()
{

}

void App::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        Update();
    }
}

void App::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(mWindow))
                {
                     mIsRunning = false;
                }
        }
    }
}