#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"

namespace neu
{
	void SpriteComponent::Update()
	{

	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.Draw(m_texture, m_owner->m_transform);
	}
}
