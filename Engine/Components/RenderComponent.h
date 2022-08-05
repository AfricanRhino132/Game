#pragma once
#include "FrameWork/Component.h"

namespace neu
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		RenderComponent() = default;

		virtual void Draw(Renderer& renderer) = 0;
	};
}