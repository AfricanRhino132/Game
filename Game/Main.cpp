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
    texture->Create(neu::g_renderer, "sf2.bmp");

    float angle = 0;

    std::cout << __FILE__ << std::endl;
    std::cout << __LINE__ << std::endl;
    std::cout << __FUNCTION__ << std::endl;

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

        //render
        neu::g_renderer.BeginFrame();
        // draw
        neu::g_renderer.Draw(texture, { 400, 300 }, angle, { 2, 2 },  { 0.5f, 1.0f });
        neu::g_renderer.EndFrame();
    }

    neu::g_renderer.Shutdown();
    neu::g_audioSystem.Shutdown();
}