#pragma once
#include "../Math/Transform.h"

namespace neu
{
	class GameObject
	{
	public:

		GameObject() = default;
		~GameObject() = default;
		
		virtual void Update() = 0;
	};
}