#pragma once
#include "FrameWork/Component.h"
#include "Physics/Collision.h"
#include "Physics/PhysicsSystem.h"

#include <functional>

namespace neu
{
	class CollisionComponent : public Component, public ICollision
	{
	public:
		using functionPtr = std::function<void(Actor*)>;

	public:
		virtual void Initialize() override;

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		virtual void OnCollisionEnter(Actor* other) override;

		virtual void OnCollisionExit(Actor* other) override;

		void SetCollisionEnter(functionPtr function) { m_enterFunction = function; }
		void SetCollisionExit(functionPtr function) { m_exitFunction = function; }

	private:
		PhysicsSystem::CollisionData data;

		functionPtr m_enterFunction;
		functionPtr m_exitFunction;
	};
}