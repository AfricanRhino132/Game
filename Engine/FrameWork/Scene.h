#pragma once
#include <list>
#include <memory>
#include "Actor.h"

namespace neu
{
	class Renderer;

	class Game;

	class Scene
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game { game } {};
		~Scene() = default;

		void Update();
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);

		void Clear();

		//void RemoveActor(Actor* actor);

		template<typename T>
		T* GetActor();

		Game* GetGame() { return m_game; }

		void SetGame(Game* game) { m_game = game; }

	private:
		Game* m_game;

		std::list<std::unique_ptr<Actor>> m_actors;

	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}
		
		return nullptr;
	}
}