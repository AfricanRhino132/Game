#pragma once
#include "FrameWork/Component.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"

namespace neu
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		RenderComponent() = default;

		virtual void Draw(Renderer& renderer) = 0;

		virtual Rect& GetSource() { return source; }

		void SetFlipHorizontal(bool flip = true) { flipHorizontal = flip; }
		bool GetFlipHorizontal() { return flipHorizontal; }

		void setRegistration(const Vector2& v) { registration = v; }

	protected:
		Rect source;
		bool flipHorizontal = false;
		Vector2 registration{ 0.5f, 0.5f };
	};
}