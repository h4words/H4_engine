#pragma once

#include <glm/ext/vector_float2.hpp>
#include <string>
#include <SDL.h>
#include <glad/glad.h>
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
#include <vector>
#include <renderer/Window.hpp>

namespace H4_engine
{
    class Window;
	class Renderer
	{
		public:
			Renderer(Window *window);
		    ~Renderer();
			void render(double delta);
            void resize(int width, int height);
			
            Camera* get_camera() { return m_camera; }

	        Shader* get_shader() { return m_shader; }
			Shader* get_text_shader() { return m_text_shader; }
			Shader* get_ui_shader() { return m_ui_shader; }
			Shader* get_depth_shader() { return m_depth_shader; }

			void set_skybox(Skybox *skybox) { m_skybox = skybox; }
			void set_camera(Camera *camera) { m_camera = camera; }

            void add_light(Light *light) { m_lights.push_back(light); }
		private:
            Window *m_window;

            Shader *m_shader;
			Shader *m_skybox_shader;
			Shader *m_text_shader;
			Shader *m_ui_shader;
			Shader *m_depth_shader;

            Camera *m_camera;

			Skybox *m_skybox;

			CubemapArrayTexture *m_depthCubemaps;
			ArrayTexture *m_depthMaps;

            std::vector<Light*> m_lights;
	};
}