#include "InputSystem.h"

#include <SDL.h>
#include <iostream>

namespace neu
{
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_w = SDL_SCANCODE_W;
	const uint32_t key_a = SDL_SCANCODE_A;
	const uint32_t key_s = SDL_SCANCODE_S;
	const uint32_t key_d = SDL_SCANCODE_D;
	const uint32_t key_esc = SDL_SCANCODE_ESCAPE;
	const uint32_t mouse_left = 0;
	const uint32_t mouse_middle = 1;
	const uint32_t mouse_right = 2;
	const uint32_t key_shiftL = SDL_SCANCODE_LSHIFT;
	const uint32_t key_semicolon = SDL_SCANCODE_SEMICOLON;
	const uint32_t key_i = SDL_SCANCODE_I;
	const uint32_t key_l = SDL_SCANCODE_L;
	const uint32_t key_j = SDL_SCANCODE_J;
	const uint32_t key_k = SDL_SCANCODE_K;
	const uint32_t key_enter = SDL_SCANCODE_RETURN;
	const uint32_t key_up = SDL_SCANCODE_UP;
	const uint32_t key_down = SDL_SCANCODE_DOWN;

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);

		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;

	}

	void InputSystem::Shutdown()
	{

	}

	InputSystem::State InputSystem::GetKeyState(uint32_t key)
	{
		State keyState = State::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if (keyDown && prevKeyDown)
		{
			keyState = State::Held;
		}
		else if (keyDown && !prevKeyDown)
		{
			keyState = State::Pressed;
		}
		else if (!keyDown && prevKeyDown)
		{
			keyState = State::Released;
		}

		// set the keyState if keyDown (true) and prevKeyDown (true) 
		// set the keyState if keyDown (true) and prevKeyDown (false) 
		// set the keyState if keyDown (false) and prevKeyDown (true) 
		// set the keyState if keyDown (false) and prevKeyDown (false) 

		return keyState;
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//Save previous keyboard state
		m_prevKeyboardState = m_keyboardState;

		//get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);

		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePos = neu::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]

		//std::cout << (bool)m_keyboardState[SDL_SCANCODE_SPACE] << std::endl;

		/*for (auto state : m_keyboardState)
		{
			std::cout << (bool)state;
		}
		std::cout << std::endl;*/
	}

	InputSystem::State InputSystem::GetButtonState(int button)
	{
		State keyState = State::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		if (buttonDown && prevButtonDown)
		{
			keyState = State::Held;
		}
		else if (buttonDown && !prevButtonDown)
		{
			keyState = State::Pressed;
		}
		else if (!buttonDown && prevButtonDown)
		{
			keyState = State::Released;
		}

		// set the keyState if buttonDown (true) and prevButtonDown (true) 
		// fill in the remaining states 

		return keyState;
	}
}