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

		void ApplyForce(const Vector2& force) { acceleration += force; };

	public:

		Vector2 velocity;
		Vector2 acceleration;

		float damping = 1;
	};
}