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

    

    auto actor = m_owner->GetScene()->GetActorsFromTag("Player");
    if (actor[0])
    {
        float dist = m_owner->m_transform.position.Distance(actor[0]->m_transform.position);

        auto sprAnim = m_owner->GetComponent<neu::SpriteAnimComponent>();


        if ( dist <= follow_dist || isFollowing)
        {
            
            isFollowing = true;

            neu::Vector2 direction = actor[0]->m_transform.position - m_owner->m_transform.position;

            if (std::fabs(direction.x) > std::fabs(direction.y))
            {
                direction = direction.x > 0 ? neu::Vector2::right : neu::Vector2::left;
            }
            else
            {
                direction = direction.y > 0 ? neu::Vector2::down : neu::Vector2::up;
            }

            if (std::fabs(dist) > attack_range)
            {
                


                if (colliding)
                {
                    neu::Vector2 dirToPlayer = colliding->m_transform.position - m_owner->m_transform.position;

                    if (std::fabs(dirToPlayer.x) > std::fabs(dirToPlayer.y))
                    {
                        dirToPlayer = dirToPlayer.x > 0 ? neu::Vector2::right : neu::Vector2::left;
                    }
                    else
                    {
                        dirToPlayer = dirToPlayer.y > 0 ? neu::Vector2::down : neu::Vector2::up;
                    }

                    if (direction == dirToPlayer)
                    {
                        prevDirection = direction;
                        direction = neu::Vector2::zero;
                    }
                }
                auto component = m_owner->GetComponent<neu::PhysicsComponent>();
                if (component) component->SetLinearVelocity(direction * speed);

                if (sprAnim)
                {
                    if (std::fabs(direction.x) > 0)
                    {
                        sprAnim->SetFlipHorizontal(direction.x > 0);
                        sprAnim->SetSequence("LeftRun");
                    }
                    else if (std::fabs(direction.y) > 0)
                    {
                        sprAnim->SetSequence(direction.y > 0 ? "ForwardRun" : "UpRun");
                    }
                }
            }
            else
            {
                direction = neu::Vector2::zero;

                auto component = m_owner->GetComponent<neu::PhysicsComponent>();
                if (component) component->SetLinearVelocity(0);

                if (atk_timer <= 0)
                {

                    if (attack_range > 100)
                    {
                        auto projectile = neu::Factory::Instance().Create<neu::Actor>(projectile_name);

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
                    
                    if (sprAnim)
                    {
                        if (std::fabs(prevDirection.x) > 0)
                        {
                            sprAnim->SetFlipHorizontal(prevDirection.x > 0);
                            if (sprAnim->m_sequence->name == "LeftAtk" && sprAnim->frame == sprAnim->m_sequence->end_frame)
                            {
                                sprAnim->frame = sprAnim->m_sequence->start_frame;
                            }
                            else
                            {
                                sprAnim->SetSequence("LeftAtk");
                            }
                            
                        }
                        else
                        {
                            if ((sprAnim->m_sequence->name == "ForwardAtk" && sprAnim->frame == sprAnim->m_sequence->end_frame) || (sprAnim->m_sequence->name == "UpAtk" && sprAnim->frame == sprAnim->m_sequence->end_frame))
                            {
                                sprAnim->frame = sprAnim->m_sequence->start_frame;
                            }
                            else
                            {
                                sprAnim->SetSequence(prevDirection.y > 0 ? "ForwardAtk" : "UpAtk");
                            }
                        }
                    }

                    neu::Vector2 dirToPlayer = actor[0]->m_transform.position - m_owner->m_transform.position;

                    if (std::fabs(dirToPlayer.x) > std::fabs(dirToPlayer.y))
                    {
                        dirToPlayer = dirToPlayer.x > 0 ? neu::Vector2::right : neu::Vector2::left;
                    }
                    else
                    {
                        dirToPlayer = dirToPlayer.y > 0 ? neu::Vector2::down : neu::Vector2::up;
                    }


                    if (prevDirection == dirToPlayer)
                    {
                        auto hitbox = neu::Factory::Instance().Create<neu::Actor>("HitBox");

                        hitbox->m_transform.position = m_owner->m_transform.position + m_owner->GetComponent<neu::CollisionComponent>()->GetSize() * prevDirection;

                        hitbox->GetComponent<neu::CollisionComponent>()->SetSize({ attack_range });

                        hitbox->SetLifespan(0.5);

                        hitbox->SetTag(std::to_string(m_owner->GetComponent<neu::CharacterComponent>()->damage));

                        hitbox->Initialize();

                        hitbox->SetParent(m_owner);

                        m_owner->GetScene()->Add(std::move(hitbox));
                    }

                    atk_timer = 5;
                }
                else
                {
                    if (std::fabs(prevDirection.y) > 0)
                    {
                        if (sprAnim)
                        {
                            if ((sprAnim->m_sequence->name != "ForwardAtk" && sprAnim->m_sequence->name != "UpAtk") || sprAnim->lastFrame == sprAnim->m_sequence->end_frame)
                            {
                                sprAnim->SetSequence(prevDirection.y > 0 ? "ForwardIdle" : "UpIdle");
                            }
                        }
                    }
                }
            }

            if (direction != neu::Vector2::zero)
            {
                prevDirection = direction;
            }
        }
    }
}

void EnemyComponent::OnCollisionEnter(neu::Actor* other)
{
    if (other->GetName() == "HitBox" && other->GetParent()->GetTag() == "Player")
    {
        neu::Event event;
        event.name = "EVENT_DAMAGE";
        event.data = std::stof(other->GetTag());
        event.receiver = this;

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
    READ_DATA(value, projectile_name);

    return true;
}