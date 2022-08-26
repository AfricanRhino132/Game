#include "TrashGame.h"
#include "Engine.h"

void TrashGame::Initialize()
{
	m_scene = std::make_unique<neu::Scene>();

    rapidjson::Document document;

    std::vector<std::string> sceneNames = { "Scenes/tilemap.txt", "Scenes/prefabs.txt", "Scenes/level.txt" };

    for (auto sceneName : sceneNames)
    {
        bool success = neu::json::Load(sceneName, document);

        if (!success)
        {
            LOG("Could not read scene %s", sceneName.c_str());

            continue;
        }

        m_scene->Read(document);
    }
    
    m_scene->Initialize();

    auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");

    actor->m_transform.position = { 600, 100 };

    actor->Initialize();

    m_scene->Add(std::move(actor));
}

void TrashGame::Shutdown()
{
    m_scene->Clear();
}

void TrashGame::Update()
{
    m_scene->Update();
}

void TrashGame::Draw(neu::Renderer& renderer)
{
    m_scene->Draw(renderer);
}
