#include "Engine.h"
#include "TrashGame.h"

#include <iostream>

int main()
{
    neu::InitializeMemory();
    neu::SetFilePath("../Assets");

    neu::g_renderer.Initialize();
    neu::g_inputSystem.Initialize();
    neu::g_audioSystem.Initialize();
    neu::g_resources.Initialize();
    neu::g_physics.Initialize();
    neu::g_eventManager.Initialize();

    neu::Engine::Instance().Register();

    neu::g_renderer.CreateWindow("Neumont", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color::black);

    std::unique_ptr<TrashGame> game = std::make_unique<TrashGame>();

    game->Initialize();

    bool quit = false;
    while (!quit)
    {
        //update
        neu::g_time.Tick();
        neu::g_inputSystem.Update();
        neu::g_audioSystem.Update();
        neu::g_physics.Update();
        neu::g_eventManager.Update();

        if (neu::g_inputSystem.GetKeyState(neu::key_esc) == neu::InputSystem::State::Pressed)
        {
            quit = true;
        }

        game->Update();

        //render
        neu::g_renderer.BeginFrame();
        // draw
        game->Draw(neu::g_renderer);
        neu::g_renderer.EndFrame();
    }
    game->Shutdown();
    game.reset();

    neu::Factory::Instance().Shutdown();

    neu::g_eventManager.Shutdown();
    neu::g_physics.Shutdown();
    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
    neu::g_resources.Shutdown();
    neu::g_inputSystem.Shutdown();
}