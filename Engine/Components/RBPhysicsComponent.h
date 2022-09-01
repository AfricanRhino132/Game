#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace neu
{
	class RBPhysicsComponent : public PhysicsComponent
	{
	public:
		RBPhysicsComponent() = default;
		~RBPhysicsComponent();

		CLASS_DECLARATION(RBPhysicsComponent)

		void Initialize() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Update() override;

		virtual void ApplyForce(const Vector2& force) override;
		virtual void SetLinearVelocity(const Vector2& force) override;

		friend class CollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}