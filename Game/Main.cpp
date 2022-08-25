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
    neu::g_physics.Initialize();

    neu::Engine::Instance().Register();

    neu::g_renderer.CreateWindow("Neumont", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color::black);

    neu::Scene scene;

    rapidjson::Document document;
    bool success = neu::json::Load("level.txt", document);
    assert(success);

    scene.Read(document);
    scene.Initialize();

    auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");

    actor->m_transform.position = { 600, 100 };

    actor->Initialize();

    scene.Add(std::move(actor));

    bool quit = false;
    while (!quit)
    {
        //update
        neu::g_time.Tick();
        neu::g_inputSystem.Update();
        neu::g_audioSystem.Update();
        neu::g_physics.Update();

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

    neu::g_physics.Shutdown();
    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
    neu::g_resources.Shutdown();
    neu::g_inputSystem.Shutdown();
}