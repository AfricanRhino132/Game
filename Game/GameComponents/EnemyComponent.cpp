#include "EnemyComponent.h"
#include "Engine.h"
#include "ProjectileComponent.h"
#include <iostream>

void EnemyComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void EnemyComponent::Update()
{
    atk_timer -= neu::g_time.deltaTime;

    auto actor = m_owner->GetScene()->GetActorFromName("Player");
    if (actor)
    {
        float dist = m_owner->m_transform.position.Distance(actor->m_transform.position);

        if ( dist <= follow_dist || isFollowing)
        {
            
            isFollowing = true;

            neu::Vector2 direction = actor->m_transform.position - m_owner->m_transform.position;

            if (std::fabs(direction.x) > std::fabs(direction.y))
            {
                direction = direction.x > 0 ? neu::Vector2::right : neu::Vector2::left;
            }
            else
            {
                direction = direction.y > 0 ? neu::Vector2::down : neu::Vector2::up;
            }

            if (dist > attack_range)
            {
                auto component = m_owner->GetComponent<neu::PhysicsComponent>();
                if (component) component->SetLinearVelocity(direction * speed);
            }
            else
            {
                if (atk_timer <= 0)
                {
                    auto projectile = neu::Factory::Instance().Create<neu::Actor>("ghostAtk");

                    projectile->m_transform.position = m_owner->m_transform.position;

                    projectile->Initialize();

                    auto projectileComp = projectile->GetComponent<ProjectileComponent>();

                    if (projectileComp)
                    {
                        projectileComp->SetDirection(direction);
                    }

                    m_owner->GetScene()->Add(std::move(projectile));

                    atk_timer = 5;
                }
            }
        }
    }
}

void EnemyComponent::OnCollisionEnter(neu::Actor* other)
{
    if (other->GetTag() == "Player")
    {
        neu::Event event;

        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.receiver = other;

        neu::g_eventManager.Notify(event);
    }
}

void EnemyComponent::OnCollisionExit(neu::Actor* other)
{
}

void EnemyComponent::OnNotify(const neu::Event& event)
{
    if (event.name == "EVENT_DAMAGE")
    {
        health -= std::get<float>(event.data);
        if (health <= 0)
        {
            m_owner->SetDestroy();
        }
    }

}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);

    READ_DATA(value, follow_dist);
    READ_DATA(value, attack_range);

    return true;
}