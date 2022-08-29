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

    

    neu::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&TrashGame::OnAddPoints, this, std::placeholders::_1));
}   

void TrashGame::Shutdown()
{
    m_scene->Clear();
}

void TrashGame::Update()
{
    switch (m_gameState)
    {
    case TrashGame::gameState::titleScreen:
        if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::Pressed)
        {
            
            m_gameState = gameState::startLevel;
        }

        break;

    case TrashGame::gameState::startLevel:
        for (int i = 0; i < 10; i++)
        {
            auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");

            actor->m_transform.position = { neu::random(600), neu::random(100)};

            actor->Initialize();

            m_scene->Add(std::move(actor));
        }

        m_gameState = gameState::game;

        break;

    case TrashGame::gameState::game:
        break;
    case TrashGame::gameState::playerDead:
        m_stateTimer -= neu::g_time.deltaTime;

        if (m_stateTimer <= 0)
        {
            m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
        }
        
        break;
    case TrashGame::gameState::gameOver:
        break;
    default:
        break;
    }

    m_scene->Update();
}

void TrashGame::Draw(neu::Renderer& renderer)
{
    m_scene->Draw(renderer);
}

void TrashGame::OnAddPoints(const neu::Event& event)
{
    std::cout << event.name << std::endl;
    std::cout << GetScore() << std::endl;
}

void TrashGame::OnPlayerDead(const neu::Event& event)
{
    m_gameState = gameState::playerDead;
    m_stateTimer = 3;
    m_lives--;
}
