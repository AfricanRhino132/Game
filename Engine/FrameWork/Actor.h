#pragma once
#include "GameObject.h"
#include "../Renderer/Model.h"


namespace neu
{
	class Scene;

	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(const Model& model, const Transform& transform) : GameObject{ transform }, m_model{ model } {}

		virtual void Update() override {}
		virtual void Draw(Renderer& renderer);

		float GetRadius() { return m_model.GetRadius(); }

		virtual void OnCollision(Actor* other) {};

		bool IsDead() { return m_dead; }

		friend class Scene;
		Model m_model;
	protected:
		bool m_destroy = false;

		
		Scene* m_scene = nullptr;

		Vector2 m_velocity;

		float m_damping = 1;

		bool m_dead = false;

	};
}
