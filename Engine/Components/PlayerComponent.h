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

		void SetControls(uint8_t kL, uint8_t kR, uint8_t kU, uint8_t kD, uint8_t kA);

		void Update() override;

	public:
		float jump = 5;		

		uint8_t left;
		uint8_t right;
		uint8_t up;
		uint8_t down;
		uint8_t atk;

		int m_groundCount = 0;

		
	};
}
