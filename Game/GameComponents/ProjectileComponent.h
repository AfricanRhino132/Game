#pragma once
#pragma once
#include "FrameWork/Component.h"

class ProjectileComponent : public neu::Component
{
public:
	CLASS_DECLARATION(ProjectileComponent)

	virtual void Initialize() override;
	virtual void Update() override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

	void SetDirection(const neu::Vector2& dir) { direction = dir; }

protected:
	neu::Vector2 direction{ neu::Vector2::zero };

	float speed = 0;

	float delay = 0;
};