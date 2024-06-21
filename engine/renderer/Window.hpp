#pragma once

#include <glm/ext/vector_float2.hpp>
#include <string>
#include <Scene.hpp>
#include "Event.hpp"
#include <functional>
#include <Log.hpp>
#include <glm/glm.hpp>
#include <components/Camera.hpp>
#include <renderer/Shader.hpp>
#include <gui/Font.hpp>
#include <gui/UI_Image.hpp>
#include <components/Light.hpp>

#include <renderer/Skybox.hpp>
#include <renderer/FrameBuffer.hpp>
#include "renderer/ArrayTexture.hpp"
#include <SDL.h>
#include <glad/glad.h>

namespace H4_engine
{
	class Window
	{
		public:
			Window(std::string title, int width, int height);
		    ~Window();
		    bool shouldClose() { return m_shouldClose; }
			void render() { SDL_GL_SwapWindow(m_pWindow); }
			void poll_events();
	        int get_width() { return m_data.width; }
	        int get_height() { return m_data.height; }

	        glm::vec2 get_current_cursor_position() { return {m_mouseX, m_mouseY}; }
		private:
		    struct WindowData
			{
		    	std::string title;
		        int width;
		        int height;
		    };
			bool m_shouldClose = false;
		    int init();
		    void shutdown();
			int m_mouseX;
			int m_mouseY;
		    SDL_Window* m_pWindow = nullptr;
			SDL_GLContext m_pGLcontext = nullptr;
		    WindowData m_data;
	};
}