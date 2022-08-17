#include "Engine.h"

#include <iostream>

int main()
{
    neu::InitializeMemory();
    neu::SetFilePath("../Assets");

    neu::g_renderer.Initialize();
    neu::g_inputSystem.Initialize();
    neu::g_audioSystem.Initialize();
    neu::g_resources.Initialize();

    neu::Engine::Instance().Register();

    neu::g_renderer.CreateWindow("Neumont", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color::black);

    neu::Scene scene;

    rapidjson::Document document;
    bool success = neu::json::Load("level.txt", document);
    assert(success);

    scene.Read(document);

    bool quit = false;
    while (!quit)
    {
        //update
        neu::g_time.Tick();
        neu::g_inputSystem.Update();
        neu::g_audioSystem.Update();

        if (neu::g_inputSystem.GetKeyState(neu::key_esc) == neu::InputSystem::State::Pressed)
        {
            quit = true;
        }

        scene.Update();

        //render
        neu::g_renderer.BeginFrame();
        // draw
        scene.Draw(neu::g_renderer);
        neu::g_renderer.EndFrame();
    }

    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
    neu::g_resources.Shutdown();
}