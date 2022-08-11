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
    texture->Create(neu::g_renderer, "Sprites/spaceShip.png");

    std::shared_ptr<neu::Model> model = std::make_shared<neu::Model>();
    model->Create("Models/Ship.txt");

    neu::g_audioSystem.AddAudio("laser", "audio/spacelasershot.wav");

    neu::Scene scene;

    //Create actors
    neu::Transform transform{ { 400, 300 }, 0, { 3, 3 } };
    std::unique_ptr<neu::Actor> actor = std::make_unique<neu::Actor>(transform);
    std::unique_ptr<neu::PlayerComponent> component = std::make_unique<neu::PlayerComponent>();
    //std::unique_ptr<neu::SpriteComponent> s_component = std::make_unique<neu::SpriteComponent>();
    std::unique_ptr<neu::AudioComponent> a_component = std::make_unique<neu::AudioComponent>();
    std::unique_ptr<neu::PhysicsComponent> p_component = std::make_unique<neu::PhysicsComponent>();
    std::unique_ptr<neu::ModelComponent> m_component = std::make_unique<neu::ModelComponent>();

    //s_component->m_texture = texture;

    m_component->m_model = model;

    a_component->m_soundName = "laser";
 
    actor->AddComponent(std::move(component));
    //actor->AddComponent(std::move(s_component));
    actor->AddComponent(std::move(a_component));
    actor->AddComponent(std::move(p_component));
    actor->AddComponent(std::move(m_component));

    neu::Transform transformc{ { 10, 5 }, 0, { 1, 1 } };
    std::unique_ptr<neu::Actor> child = std::make_unique<neu::Actor>(transformc);
    std::unique_ptr<neu::ModelComponent> m_componentc = std::make_unique<neu::ModelComponent>();
    m_componentc->m_model = model;
    child->AddComponent(std::move(m_componentc));

    actor->AddChild(std::move(child));

    scene.Add(std::move(actor));

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
}