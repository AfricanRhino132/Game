#pragma once
#include "FrameWork/Component.h"

namespace neu
{
	class AudioComponent : public Component
	{
	public:
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		std::string m_soundName;
		bool m_playOnAwake = false;
		float m_volume = 1;
		float m_pitch = 1;
		bool m_loop = false;

		virtual void Update() override;

		void Play();

		void Stop();
	};
}