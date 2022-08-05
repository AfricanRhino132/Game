#include "Engine.h"

#include <iostream>



int main()
{
    neu::SetFilePath("../Assets");

    neu::InitializeMemory();

    neu::g_renderer.Initialize();
    neu::g_inputSystem.Initialize();
    neu::g_audioSystem.Initialize();

    neu::Color black{ 0, 0, 0, 255 };
    neu::Color white{ 255, 255, 255, 255 };

    neu::g_renderer.CreateWindow("Neumont", 800, 600);
    neu::g_renderer.SetClearColor(black);

    std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
    texture->Create(neu::g_renderer, "jesus.png");

    neu::Scene scene;

    //Create actors
    neu::Transform transform{ { 100, 100 }, 90, { 1, 1 } };
    std::unique_ptr<neu::Actor> actor = std::make_unique<neu::Actor>(transform);
    std::unique_ptr<neu::PlayerComponent> component = std::make_unique<neu::PlayerComponent>();
    std::unique_ptr<neu::SpriteComponent> s_component = std::make_unique<neu::SpriteComponent>();

    s_component->m_texture = texture;
    
    actor->AddComponent(std::move(component));
    actor->AddComponent(std::move(s_component));

    scene.Add(std::move(actor));

    float angle = 0;

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

        angle += 360.0f * neu::g_time.deltaTime;

        scene.Update();

        //render
        neu::g_renderer.BeginFrame();
        // draw
        scene.Draw(neu::g_renderer);
        neu::g_renderer.Draw(texture, { 400, 300 }, angle, { 1, 1 },  { 0.5f, 1.0f });
        neu::g_renderer.EndFrame();
    }

    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
}