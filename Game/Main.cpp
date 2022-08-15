#include "Engine.h"

#include <iostream>



int main()
{
    neu::SetFilePath("../Assets");

    neu::InitializeMemory();

    neu::g_renderer.Initialize();
    neu::g_inputSystem.Initialize();
    neu::g_audioSystem.Initialize();
    neu::g_resources.Initialize();

    neu::Engine::Instance().Register();

    neu::g_renderer.CreateWindow("Neumont", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color::black);

    neu::g_audioSystem.AddAudio("laser", "audio/spacelasershot.wav");

    neu::Scene scene;

    //Create actors
    neu::Transform transform{ { 400, 300 }, 0, { 1, 1 } };
    //std::unique_ptr<neu::Actor> actor = std::make_unique<neu::Actor>(transform);
    std::unique_ptr<neu::Actor> actor = neu::Factory::Instance().Create<neu::Actor>("Actor");
    actor->m_transform = transform;
    std::unique_ptr<neu::Component> component = neu::Factory::Instance().Create<neu::Component>("PlayerComponent");
    std::unique_ptr<neu::SpriteComponent> s_component = neu::Factory::Instance().Create<neu::SpriteComponent>("SpriteComponent");
    std::unique_ptr<neu::AudioComponent> a_component = neu::Factory::Instance().Create<neu::AudioComponent>("AudioComponent");
    std::unique_ptr<neu::Component> p_component = neu::Factory::Instance().Create<neu::Component>("PhysicsComponent");
    std::unique_ptr<neu::ModelComponent> m_component = neu::Factory::Instance().Create<neu::ModelComponent>("ModelComponent");

    s_component->m_texture = neu::g_resources.Get<neu::Texture>("sprites/playership.png", neu::g_renderer);

    m_component->m_model = neu::g_resources.Get<neu::Model>("models/ship.txt");

    a_component->m_soundName = "laser";
 
    actor->AddComponent(std::move(component));
    actor->AddComponent(std::move(s_component));
    actor->AddComponent(std::move(a_component));
    actor->AddComponent(std::move(p_component));
    //actor->AddComponent(std::move(m_component));

    neu::Transform transformc{ { 10, 5 }, 0, { 1, 1 } };
    std::unique_ptr<neu::Actor> child = std::make_unique<neu::Actor>(transformc);
    std::unique_ptr<neu::ModelComponent> m_componentc = std::make_unique<neu::ModelComponent>();
    m_componentc->m_model = neu::g_resources.Get<neu::Model>("models/ship.txt");
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
    neu::g_resources.Shutdown();
}