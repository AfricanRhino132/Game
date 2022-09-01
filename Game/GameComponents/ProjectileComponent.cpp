#include "ProjectileComponent.h"
#include "FrameWork/Actor.h"
#include "Components/PhysicsComponent.h"

void ProjectileComponent::Initialize()
{
	
}

void ProjectileComponent::Update()
{
	auto physComp = m_owner->GetComponent<neu::PhysicsComponent>();

	if (physComp) 
	{
		physComp->SetLinearVelocity(direction * speed);
	}
}

bool ProjectileComponent::Write(const rapidjson::Value& value) const
{
	return true;
}

bool ProjectileComponent::Read(const rapidjson::Value& value)
{
	READ_DATA(value, speed);

	return true;
}
