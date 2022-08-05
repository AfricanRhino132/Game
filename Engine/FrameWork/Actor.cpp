#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Components/RenderComponent.h"

namespace neu
{
	void Actor::Update()
	{
		for (auto& component : m_components)
		{
			component->Update();
		}
	}

	void neu::Actor::Draw(Renderer& renderer)
	{
		for (auto& component : m_components)
		{
			auto renderComponent = dynamic_cast<RenderComponent*>(component.get());
			//Draw some shiz
			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;

		m_components.push_back(std::move(component));
	}
}
