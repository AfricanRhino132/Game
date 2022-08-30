#pragma once
#include "FrameWork/Component.h"
#include "Math/Rect.h"

namespace neu
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		RenderComponent() = default;

		virtual void Draw(Renderer& renderer) = 0;

		virtual Rect& GetSource() { return source; }

	protected:
		Rect source;
	};
}