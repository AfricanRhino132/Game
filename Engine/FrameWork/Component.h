#pragma once
#include "GameObject.h"

namespace neu
{
	class Actor;

	class Component : public GameObject
	{
	public:
		Component() = default;
		~Component() = default;

		virtual void Update() = 0;

		friend class Actor;

	protected:
		Actor* m_owner = nullptr;
	};
}