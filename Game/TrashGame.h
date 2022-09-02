#pragma once
#include "FrameWork/Game.h"
#include "FrameWork/Event.h"


class TrashGame : public neu::Game, public neu::INotify
{
public:
	enum class gameState
	{
		titleScreen,
		startLevel,
		game,
		playerDead,
		gameOver
	};

	enum class TitleScreenState
	{
		playGame,
		exitGame
	};

public:
	virtual void Initialize() override;
	virtual void Shutdown() override;
	
	virtual void Update() override;
	virtual void Draw(neu::Renderer& renderer) override;

	virtual void OnNotify(const neu::Event& event) override;

	void OnAddPoints(const neu::Event& event);
	void OnPlayerDead(const neu::Event& event);
	void Read(const std::vector<std::string> sceneNames);

	float quit = false;

private :
	gameState m_gameState = gameState::titleScreen;
	TitleScreenState m_titleState = TitleScreenState::playGame;

	float m_stateTimer = 0;
	int m_lives = 3;

};