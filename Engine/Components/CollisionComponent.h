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

		CLASS_DECLARATION(CollisionComponent)

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		virtual void OnCollisionEnter(Actor* other) override;

		virtual void OnCollisionExit(Actor* other) override;

		void SetCollisionEnter(functionPtr function) { m_enterFunction = function; }
		void SetCollisionExit(functionPtr function) { m_exitFunction = function; }

		const Vector2& GetSize() { return data.size; }
		void SetSize(const Vector2& size) { data.size = size; }

		friend class Actor;

	private:
		PhysicsSystem::CollisionData data;

		Vector2 scale_offset{ 1.0f, 1.0f };

		functionPtr m_enterFunction;
		functionPtr m_exitFunction;
	};
}