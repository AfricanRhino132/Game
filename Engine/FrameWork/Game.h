#pragma once
#include <memory>

namespace neu
{
	class Renderer;

	class Scene;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update() = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int GetScore() { return m_score; }

		void AddPoints(int points) { m_score += points; if (m_score < 0) m_score = 0; }

	protected:
		int m_score = 0;

		std::unique_ptr<Scene> m_scene;
	};
}