#include "TrashGame.h"
#include "Engine.h"
#include "GameComponents/EnemyComponent.h"
#include "GameComponents/ProjectileComponent.h"

void TrashGame::Initialize()
{
    REGISTER_CLASS(EnemyComponent);
    REGISTER_CLASS(ProjectileComponent);

	m_scene = std::make_unique<neu::Scene>();

    Read({ "Scenes/TitleScreen.json" });


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

        //select quit game
        if (neu::g_inputSystem.GetKeyState(neu::key_down) == neu::InputSystem::Pressed && m_titleState == TitleScreenState::playGame)
        {
            m_scene->GetActorFromName("PlayGameSelection")->SetActive(false);
            m_scene->GetActorFromName("QuitGameSelection")->SetActive();
            m_titleState = TitleScreenState::exitGame;
        }

        //Select Start Game
        if (neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::Pressed && m_titleState == TitleScreenState::exitGame)
        {
            m_scene->GetActorFromName("QuitGameSelection")->SetActive(false);
            m_scene->GetActorFromName("PlayGameSelection")->SetActive();
            m_titleState = TitleScreenState::playGame;
        }

        //Start or Close Game
        if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::Pressed || neu::g_inputSystem.GetKeyState(neu::key_enter) == neu::InputSystem::Pressed)
        {
            switch (m_titleState)
            {
            case TrashGame::TitleScreenState::playGame:
                m_scene->Clear();
                Read({ "Scenes/tilemap.json", "Scenes/prefabs.json", "Scenes/level.json" });
                m_gameState = gameState::startLevel;
                break;
            case TrashGame::TitleScreenState::exitGame:
                quit = true;
                break;
            default:
                break;
            }
            
            //m_gameState = gameState::startLevel;
        }

        break;

    case TrashGame::gameState::startLevel:

    
        {   
            auto player = neu::Factory::Instance().Create<neu::Actor>("Wizard");
            //auto player2 = neu::Factory::Instance().Create<neu::Actor>("Knight");

            player->m_transform.position = { 400, 300 };
            //player2->m_transform.position = { 700, 300 };

            player->Initialize();
            //player2->Initialize();

            player->GetComponent<neu::PlayerComponent>()->SetControls(neu::key_a, neu::key_d, neu::key_w, neu::key_s, neu::key_shiftL);
            //player2->GetComponent<neu::PlayerComponent>()->SetControls(neu::key_j, neu::key_l, neu::key_i, neu::key_k, neu::key_semicolon);

            m_scene->Add(std::move(player));
            //m_scene->Add(std::move(player2));
        }

        for (int i = 0; i < 3; i++)
        {
            auto actor = neu::Factory::Instance().Create<neu::Actor>("Goblin");

            actor->m_transform.position = { neu::random(700,900), neu::random(200, 300) };

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

    m_score += 100;
}

void TrashGame::OnPlayerDead(const neu::Event& event)
{
    m_gameState = gameState::playerDead;
    m_stateTimer = 3;
    m_lives--;
}

void TrashGame::Read(const std::vector<std::string> sceneNames)
{
    rapidjson::Document document;

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
}

void TrashGame::OnNotify(const neu::Event& event)
{
    if (event.name == "EVENT_ADD_POINTS")
    {
        OnAddPoints(event);
    }
}
