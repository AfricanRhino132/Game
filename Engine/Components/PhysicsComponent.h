#pragma once
#include "FrameWork/Component.h"

namespace neu
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		CLASS_DECLARATION(PhysicsComponent)

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Update() override;

		virtual void ApplyForce(const Vector2& force) { acceleration += force; };
		virtual void SetLinearVelocity(const Vector2& force) { velocity = force; };

	public:

		Vector2 velocity;
		Vector2 acceleration;

		float damping = 1;
	};
}