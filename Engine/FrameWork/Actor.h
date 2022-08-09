#pragma once
#include "GameObject.h"
#include "Component.h"
#include <vector>


namespace neu
{
	class Scene;
	class Renderer;

	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(const Transform& transform) : m_transform{ transform } {}

		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		float GetRadius() { return 0; } // m_model.GetRadius()* std::max(m_transform.scale.x, m_transform.scale.y); }

		virtual void OnCollision(Actor* other) {};

		bool IsDead() { return m_dead; }

		friend class Scene;
		
		Transform m_transform;

	protected:
		bool m_destroy = false;

		Scene* m_scene = nullptr;

		Vector2 m_velocity;
		float m_damping = 1;

		bool m_dead = false;

		std::vector<std::unique_ptr<Component>> m_components;

	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& comp : m_components)
		{
			T* result = dynamic_cast<T*>(comp.get());
			if (result) return result;
		}

		return nullptr;
	}
}
