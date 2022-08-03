#pragma once

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
 
#include "FrameWork/Scene.h"
#include "FrameWork/Game.h"

#include "Renderer/Model.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

#include "Audio/AudioSystem.h"

#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include <memory>

namespace neu
{
	extern InputSystem g_inputSystem;
	extern Renderer g_renderer;

	extern Time g_time;

	extern AudioSystem g_audioSystem;

	
}
