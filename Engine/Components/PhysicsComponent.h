#pragma once
#include "FrameWork/Component.h"

namespace neu
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		virtual void Update() override;

		void ApplyForce(const Vector2& force) { m_acceleration += force; };

	public:

		Vector2 m_velocity;
		Vector2 m_acceleration;

		float m_damping = 1;
	};
}