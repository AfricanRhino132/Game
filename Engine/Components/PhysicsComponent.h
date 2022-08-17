#pragma once
#include "FrameWork/Component.h"

namespace neu
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		void ApplyForce(const Vector2& force) { m_acceleration += force; };

	public:

		Vector2 m_velocity;
		Vector2 m_acceleration;

		float damping = 1;
	};
}