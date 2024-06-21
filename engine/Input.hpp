#pragma once

#include "Keys.hpp"
#include <cstddef>
namespace H4_engine {

    class Input {
		public:
			static bool IsKeyPressed(const KeyCode key_code)
			{
        		return m_keys_pressed[static_cast<size_t>(key_code)];
    		};
			static void PressKey(const KeyCode key_code)
			{
        		m_keys_pressed[static_cast<size_t>(key_code)] = true;
    		};
			static void ReleaseKey(const KeyCode key_code)
			{
				m_keys_pressed[static_cast<size_t>(key_code)] = false;
			};
	        static bool IsMouseButtonPressed(const MouseButton mouse_button)
			{
				return m_mouse_buttons_pressed[static_cast<size_t>(mouse_button)];
			};
	        static void PressMouseButton(const MouseButton mouse_button)
			{
				m_mouse_buttons_pressed[static_cast<size_t>(mouse_button)] = true;
			};
	        static void ReleaseMouseButton(const MouseButton mouse_button)
			{
				m_mouse_buttons_pressed[static_cast<size_t>(mouse_button)] = false;
			};
			static void ScrollMouse(const int y)
			{
				m_scrolled_y = y;
			};
			static bool IsMouseScrolledDown()
			{
				return m_scrolled_y == -1;
			};
			static bool IsMouseScrolledUp()
			{
				return m_scrolled_y == 1;
			};
		private:
			
			inline static int m_scrolled_y = 0;
	        inline static bool m_keys_pressed[static_cast<size_t>(KeyCode::KEY_LAST) + 1] = {};
	        inline static bool m_mouse_buttons_pressed[static_cast<size_t>(MouseButton::MOUSE_BUTTON_LAST) + 1] = {};
    };
}
