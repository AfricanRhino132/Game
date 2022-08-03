#pragma once
#include <vector>
#include <cstdint>
#include "../Math/Vector2.h"
#include <array>

namespace neu
{
	class InputSystem
	{
	public:
		enum State
		{
			Idle, 
			Pressed,
			Held,
			Released
		};
	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		bool GetKeyDown(int key) { return m_keyboardState[key]; };
		bool GetPreviousKeyDown(int key) { return m_prevKeyboardState[key]; };

		State GetKeyState(uint32_t key);

		const Vector2& GetMousePosition() const { return m_mousePos; }

		State GetButtonState(int mouse);

		bool GetButtonDown(int mouse) { return m_mouseButtonState[mouse]; }

		bool GetPreviousButtonDown(int mouse) { return m_prevMouseButtonState[mouse]; }

	private:
		int m_numKeys;

		Vector2 m_mousePos;

		std::array<uint8_t, 3> m_mouseButtonState;

		std::array<uint8_t, 3> m_prevMouseButtonState;

		std::vector<uint8_t> m_keyboardState;

		std::vector<uint8_t> m_prevKeyboardState;
	};

	extern const uint32_t key_space;
	extern const uint32_t key_w;
	extern const uint32_t key_a;
	extern const uint32_t key_s;
	extern const uint32_t key_d;
	extern const uint32_t key_esc;
	extern const uint32_t mouse_left;
	extern const uint32_t mouse_middle;
	extern const uint32_t mouse_right;
	extern const uint32_t key_shiftL;
	extern const uint32_t key_i;
	extern const uint32_t key_l;
	extern const uint32_t key_j;
	extern const uint32_t key_semicolon;
	
}