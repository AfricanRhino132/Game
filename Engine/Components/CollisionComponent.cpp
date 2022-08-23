#include "CollisionComponent.h"
#include "Engine.h"

namespace neu
{
    void CollisionComponent::Initialize()
    {
        auto component = m_owner->GetComponent<RBPhysicsComponent>();

        if (component)
        {
            g_physics.SetCollisionBox(component->m_body, data, m_owner);
        }
    }

    bool CollisionComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CollisionComponent::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, data.size);
        READ_DATA(value, data.density);
        READ_DATA(value, data.friction);
        READ_DATA(value, data.restitution);
        READ_DATA(value, data.is_trigger);

        return true;
    }

    void CollisionComponent::Update()
    {

    }

    void CollisionComponent::OnCollisionEnter(Actor* other)
    {

    }

    void CollisionComponent::OnCollisionExit(Actor* other)
    {

    }
}