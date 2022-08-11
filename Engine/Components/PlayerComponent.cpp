#include "PlayerComponent.h"

#include "Engine.h"

#include <iostream>

namespace neu
{
	void PlayerComponent::Update()
	{
		Vector2 direction = Vector2::zero;

		if (g_inputSystem.GetKeyState(key_a) == InputSystem::State::Held)
		{
			m_owner->m_transform.rotation -= 180 * g_time.deltaTime;
		}
		if (g_inputSystem.GetKeyState(key_d) == InputSystem::State::Held)
		{
			m_owner->m_transform.rotation += 180 * g_time.deltaTime;
		}
		/*if (g_inputSystem.GetKeyState(key_s) == InputSystem::State::Held)
		{
			direction = Vector2::down;
		}*/
		float thrust = 0;
		if (g_inputSystem.GetKeyState(key_w) == InputSystem::State::Held)
		{
			thrust = 500;
		}

		auto component = m_owner->GetComponent<PhysicsComponent>();

		if (component)
		{
			Vector2 force = Vector2::Rotate(Vector2::right, math::DegToRad(m_owner->m_transform.rotation)) * thrust;

			component->ApplyForce(force);

		}

		m_owner->m_transform.position += direction * 300 * neu::g_time.deltaTime;

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::State::Pressed)
		{
			auto component = m_owner->GetComponent<AudioComponent>();

			if (component)
			{
				component->Play();
			}
		}
	}
}
