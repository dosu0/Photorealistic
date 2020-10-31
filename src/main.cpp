#include "App.hpp"
#include <vector>
#include <stdio.h>


// Foward Declarations
static void MainMenuBar(bool *done, bool *show_demo_window);
static void ObjectHierarchy();

int main(int argc, char *argv[])
{
    ImGuiContext *ctx=ImGui::CreateContext();
    ImGui::SetCurrentContext(ctx);
    App app(ImGui::GetIO());

    // Our state
    static bool show_demo_window = false;

    // Main loop
    static bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(app.window))
                done = true;
        }

        app.NewFrame();

        MainMenuBar(&done, &show_demo_window);
        ObjectHierarchy();
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        app.Render();
    }

    app.Quit();
    return 0;
}

void MainMenuBar(bool *done, bool *show_demo_window)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
            {
            }
            if (ImGui::MenuItem("Open...", "Ctrl+O"))
            {
            }
            if (ImGui::BeginMenu("Open Recent"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W"))
            {
                *done = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z"))
            {
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Shift+Z"))
            {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X"))
            {
            }
            if (ImGui::MenuItem("Copy", "Ctrl+C"))
            {
            }
            if (ImGui::MenuItem("Paste", "Ctrl+V"))
            {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("ImGui"))
        {
            if (ImGui::MenuItem("Show Demo Window"))
            {
                *show_demo_window = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void ObjectHierarchy()
{
    if (ImGui::Begin("Object Hierarchy"))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("New"))
            {
                if (ImGui::MenuItem("Camera"))
                {
                    // Code to add camera
                }

                if (ImGui::MenuItem("Sphere"))
                {
                    // Code to add sphere
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();
    }
    else
    {
        ImGui::End();
    }
}