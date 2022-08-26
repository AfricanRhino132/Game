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
			direction = Vector2::left;
		}
		if (g_inputSystem.GetKeyState(key_d) == InputSystem::State::Held)
		{
			direction = Vector2::right;
		}

		if (g_inputSystem.GetKeyState(key_w) == InputSystem::State::Held)
		{
			//direction = Vector2::up;
		}

		if (g_inputSystem.GetKeyState(key_s) == InputSystem::State::Held)
		{
			direction = Vector2::down;
		}

		auto component = m_owner->GetComponent<PhysicsComponent>();

		if (component)
		{
			component->ApplyForce(direction * speed);
		}

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::State::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();

			if (component)
			{
				component->ApplyForce(Vector2::up * 90);
			}
		}
	}
	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		std::cout << "Player Enter: " << std::endl;
	}

	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		std::cout << "Player Exit: " << std::endl;
	}

	void PlayerComponent::Initialize()
	{
		auto component = m_owner->GetComponent<CollisionComponent>();

		if (component)
		{
			component->SetCollisionEnter(std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1));
			component->SetCollisionExit(std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1));
		}
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}
}
