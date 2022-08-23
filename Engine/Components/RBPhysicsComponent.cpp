#include "RBPhysicsComponent.h"
#include "Engine.h"

namespace neu
{
	RBPhysicsComponent::~RBPhysicsComponent()
	{
		if (m_body)
		{
			g_physics.DestroyBody(m_body);
		}
	}

	void RBPhysicsComponent::Initialize()
	{
		m_body = g_physics.CreateBody(m_owner->m_transform.position, m_owner->m_transform.rotation, data);
		m_body->SetGravityScale(data.gravity_scale);
		m_body->SetLinearDamping(damping);
	}

	bool RBPhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool RBPhysicsComponent::Read(const rapidjson::Value& value)
	{
		PhysicsComponent::Read(value);

		READ_DATA(value, data.gravity_scale);
		READ_DATA(value, data.is_dynamic);
		READ_DATA(value, data.constrain_angle);

		return true;
	}

	void RBPhysicsComponent::Update()
	{
		m_owner->m_transform.position = PhysicsSystem::WorldToScreen(B2VEC2_TO_VECTOR2(m_body->GetPosition()));

		m_owner->m_transform.rotation = m_body->GetAngle();
	}

	void RBPhysicsComponent::ApplyForce(const Vector2& force)
	{
		m_body->ApplyForceToCenter(VECTOR2_TO_B2VEC2(force), true);
	}
}