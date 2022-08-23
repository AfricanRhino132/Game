#pragma once

#include "Serialization/Json.h"

#include "Physics/PhysicsSystem.h"

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
 
#include "FrameWork/Scene.h"
#include "FrameWork/Game.h"
#include "FrameWork/Singleton.h"
#include "FrameWork/Factory.h"

#include "Renderer/Model.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Renderer.h"

#include "Input/InputSystem.h"

#include "Resource/ResourceManager.h"

#include "Audio/AudioSystem.h"

#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Components/SpriteAnimComponent.h"

#include <memory>

namespace neu
{
	extern InputSystem g_inputSystem;
	extern Renderer g_renderer;
	extern Time g_time;
	extern AudioSystem g_audioSystem;
	extern ResourceManager g_resources;
	extern PhysicsSystem g_physics;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();
	};
}
