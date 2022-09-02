#include "ProjectileComponent.h"
#include "FrameWork/Actor.h"
#include "Components/PhysicsComponent.h"
#include "Engine.h"

void ProjectileComponent::Initialize()
{
	
}

void ProjectileComponent::Update()
{

	delay -= neu::g_time.deltaTime;

	auto physComp = m_owner->GetComponent<neu::PhysicsComponent>();

	if (physComp && delay <= 0) 
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
	READ_DATA(value, delay);

	return true;
}
