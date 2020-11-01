/**
    Main file for Photorealistic
    @file main.cpp
    @author Platinum-Phoenix
    @version 0.1.0
*/

#include "App.hpp"

int main(int argc, char* argv[])
{
    App app;

    bool success = app.Init();

    if (success)
    {
        app.RunLoop();
    }

    app.Quit();
    return 0;
}