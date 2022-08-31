#pragma once

#include "CharacterComponent.h"

namespace neu
{
	class PlayerComponent : public CharacterComponent
	{
	public:
		PlayerComponent() = default;

		CLASS_DECLARATION(PlayerComponent)

		void Initialize() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual void OnNotify(const Event& event) override;

		void Update() override;

	public:
		float jump = 3000;		

		int m_groundCount = 0;
	};
}
