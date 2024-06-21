#pragma once
#include <string>
#include <Event.hpp>
#include <Scene.hpp>
#include <SDL.h>
#include <renderer/Renderer.hpp>
#include <renderer/Window.hpp>
#include <audio/AudioSystem.hpp>

#define TICK_RATE 64

namespace H4_engine
{
	class Application
	{
		public:
			Application() { instance = this; };
			int start(unsigned int window_width, unsigned int window_height, std::string title);
			static Application* get_instance() { return instance; };
			Window* get_window() { return m_Window; };
			AudioSystem* get_audioSystem() { return m_audioSystem; };
		private:
			Window* m_Window;
			Renderer* m_renderer;
			Scene* m_scene;
			AudioSystem* m_audioSystem;
		
			Font *font;
			UI_Image *img;

			glm::mat4 ui_view_projection_matrix;

			inline static Application* instance;

			double m_tick_timer = 0;
	};
}
