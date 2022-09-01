#include "PlayerComponent.h"

#include "Engine.h"

#include <iostream>

namespace neu
{
	void PlayerComponent::Update()
	{
		Vector2 direction = Vector2::zero;

		atkTimer -= neu::g_time.deltaTime;

		if (atkTimer <= 0)
		{
			isAttacking = false;
		}

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
			direction = Vector2::up;
		}

		if (g_inputSystem.GetKeyState(key_s) == InputSystem::State::Held)
		{
			direction = Vector2::down;
		}

		if (g_inputSystem.GetButtonState(mouse_left) == neu::InputSystem::State::Pressed && atkTimer <= 0)
		{
			isAttacking = true;

			atkTimer = 0.5;
			
		}

		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();

		if (component)
		{
			if (!isAttacking)
			{
				component->SetLinearVelocity(direction * speed);
				velocity = direction * speed;
			}
			else
			{
				component->SetLinearVelocity(Vector2::zero);
			}

		}

		/*if (m_groundCount > 0 && g_inputSystem.GetKeyState(key_space) == InputSystem::State::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();

			if (component)
			{
				component->ApplyForce(Vector2::up * jump);
				std::cout << "Jump" << std::endl;
			}
		}*/

		auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
		if (animComponent)
		{
			if (!isAttacking)
			{
				if (std::fabs(velocity.x) > 0)
				{
					animComponent->SetFlipHorizontal(velocity.x > 0);

					animComponent->SetSequence("LeftRun");
				}
				else if (std::fabs(velocity.y) > 0)
				{
					if (direction == Vector2::down)
					{
						animComponent->SetSequence("ForwardRun");
					}
					else
					{
						animComponent->SetSequence("UpRun");
					}
				}
				else
				{
					if (prevDirection == Vector2::down)
					{
						animComponent->SetSequence("ForwardIdle");
					}
					else
					{
						animComponent->SetFlipHorizontal(prevDirection.x > 0);
						animComponent->SetSequence("ForwardIdle");
					}
				}
			}
			else
			{
				if (std::fabs(prevDirection.x) > 0)
				{
					animComponent->SetFlipHorizontal(direction != Vector2::zero ? direction.x > 0 : prevDirection.x > 0);
					animComponent->SetSequence("AtkLeft");
				}
				else
				{
					direction == Vector2::up ? animComponent->SetSequence("AtkUp") : animComponent->SetSequence("AtkDown");
				}
				
			}

			if (direction != Vector2::zero)
			{
				prevDirection = direction;
			}
		}

		auto camera = m_owner->GetScene()->GetActorFromName("Camera"); 
		if (camera) 
		{ 
			camera->m_transform.position = m_owner->m_transform.position; 
		} 
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			if (health <= 0)
			{
				//player die
			}
		}
		if (event.name == "EVENT_HEALTH")
		{
			health += std::get<float>(event.data);
		}
	}

	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;

			g_eventManager.Notify(event);

			other->SetDestroy();
		}
		
		if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.receiver = other;

			g_eventManager.Notify(event);
		}

		if (other->GetTag() == "Ground")
		{
			m_groundCount++;
		}
	}

	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount--;
		}
	}

	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, jump);
		
		return true;
	}
}
