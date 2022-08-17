#pragma once
#include "RenderComponent.h"

namespace neu
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		virtual void Draw(Renderer& renderer) override;

	public:
		std::shared_ptr<Texture> m_texture;
	};
}