#include <Application.hpp>
#include <Log.hpp>
#include <Input.hpp>
#include <components/Model.hpp>
#include <components/CameraController.hpp>
#include <components/Light.hpp>
#include <components/ComponentFactory.hpp>
#include <audio/AudioSource.hpp>
namespace H4_engine
{
	int Application::start(unsigned int window_width, unsigned int window_height, std::string title)
	{
		instance = this;
		m_Window = new Window(title, window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
		LOG_INFO("Window {0} is initialized.", title);
		m_renderer = new Renderer(m_Window);
		m_renderer->set_skybox(new Skybox(new Cubemap({ "resources/NissiBeach2/posx.jpg"
                                          			  , "resources/NissiBeach2/negx.jpg"
                                          			  , "resources/NissiBeach2/posy.jpg"
                                          			  , "resources/NissiBeach2/negy.jpg"
                                          			  , "resources/NissiBeach2/posz.jpg"
                                          			  , "resources/NissiBeach2/negz.jpg"})));
													  
		LOG_INFO("Renderer is initialized.");

		m_audioSystem = new AudioSystem();

		m_scene = new Scene();

		m_mapLoader = new MapLoader();
		m_mapLoader->load("resources/test3.map");
		m_mapLoader->push_to_scene(m_scene);

		font = new Font("resources/arial.ttf", 48);
        img = new UI_Image(Texture2D::blank, 0, 0, 10, 10);

		ui_view_projection_matrix = glm::ortho(0.0f, static_cast<float>(window_width), 0.f, static_cast<float>(window_height), -1.f, 1.f); 

		MessageBus::Subscribe<EventWindowResize>([&](EventWindowResize event){
			m_renderer->resize(event.width, event.height);
			ui_view_projection_matrix = glm::ortho(0.0f, static_cast<GLfloat>(event.width), 0.f, static_cast<GLfloat>(event.height), -1.f, 1.f); 
		});

		double currentFrameTime = get_time();
		double lastFrameTime = currentFrameTime;
		double deltaFrameTime = 0;
		
		double av500msDuration = 0;
		int av500msFPS = 0;
		int av500msFPS_1 = 0;

		LOG_INFO("Fully initialized.");

		while(!m_Window->shouldClose())
		{
			m_Window->poll_events();
			
			double start = get_time();

			lastFrameTime = currentFrameTime;
			currentFrameTime = get_time();
			deltaFrameTime = currentFrameTime - lastFrameTime;

			m_tick_timer -= deltaFrameTime;
			if (m_tick_timer <= 0)
			{
				for	(Entity *entity : m_scene->get_objects())
				{
					entity->process_new_components();
				}

				for	(Entity *entity : m_scene->get_objects())
				{
					entity->tick();
				}
				m_tick_timer = 1000.0 / TICK_RATE;
			}
			m_renderer->render(deltaFrameTime);

			//m_shader->unbind();

			//m_ui_shader->bind();
			//m_ui_shader->set_matrix4("view_projection_matrix", ui_view_projection_matrix);
			//img->Render(1, 1, 1, 1);
			av500msDuration += deltaFrameTime;
			av500msFPS_1++;
			if (av500msDuration > 500)
			{
				av500msFPS = av500msFPS_1 * 2;
				av500msDuration = 0;
				av500msFPS_1 = 0;
			}

			Shader* text_shader = m_renderer->get_text_shader();

			text_shader->bind();
			text_shader->set_matrix4("view_projection_matrix", ui_view_projection_matrix);
			font->RenderText(text_shader, std::to_string(int(1000 / deltaFrameTime)), 25.0f, 25.0f, 1.0f, glm::vec3(1, 1, 1));
			font->RenderText(text_shader, "AV 500MS " + std::to_string(int(av500msFPS)), 25.0f, 70.0f, 1.0f, glm::vec3(1, 1, 1));

			m_Window->render();

			double end = get_time();

			float elapsedMS = end - start;

			//SDL_Delay(abs(floor(16.666f - elapsedMS)));
		}
		LOG_INFO("Exited main loop.");
		return 0;
	}

}



