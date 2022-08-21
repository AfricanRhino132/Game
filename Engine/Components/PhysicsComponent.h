#pragma once
#include "FrameWork/Component.h"

namespace neu
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		bool Write(const rapidjson::Value& value) const override;
		bool Read(const rapidjson::Value& value) override;

		void Update() override;

		void ApplyForce(const Vector2& force) { acceleration += force; };

	public:

		Vector2 velocity;
		Vector2 acceleration;

		float damping = 1;
	};
}