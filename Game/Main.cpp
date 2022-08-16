#include "Engine.h"

#include <iostream>



int main()
{
    neu::InitializeMemory();
    neu::SetFilePath("../Assets");

    rapidjson::Document document;
    bool success = neu::json::Load("json.txt", document);
    assert(success);

    std::string str;
    neu::json::Get(document, "string", str);
    std::cout << str << std::endl;

    bool b;
    neu::json::Get(document, "boolean", b);
    std::cout << b << std::endl;

    int i1;
    neu::json::Get(document, "integer1", i1);
    std::cout << i1 << std::endl;

    int i2;
    neu::json::Get(document, "integer2", i2);
    std::cout << i2 << std::endl;

    float f;
    neu::json::Get(document, "float", f);
    std::cout << f << std::endl;

    neu::Vector2 v2;
    neu::json::Get(document, "vector2", v2);
    std::cout << v2 << std::endl;

    neu::Color color;
    neu::json::Get(document, "color", color);
    std::cout << color << std::endl;

   
    

    neu::g_renderer.Initialize();
    neu::g_inputSystem.Initialize();
    neu::g_audioSystem.Initialize();
    neu::g_resources.Initialize();

    neu::Engine::Instance().Register();

    neu::g_renderer.CreateWindow("Neumont", 800, 600);
    neu::g_renderer.SetClearColor(neu::Color::black);

    neu::Scene scene;

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