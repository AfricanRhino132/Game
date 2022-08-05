#pragma once
#include "FrameWork/Component.h"

namespace neu
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent() = default;

		void Update() override;
	};
}
