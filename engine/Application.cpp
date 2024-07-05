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
		m_Window = new Window(title, window_width, window_height);
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
		m_mapLoader->load("resources/testmap.map", m_scene);

		Entity *entcam = new Entity();
		Transform* enttr = entcam->add_component<Transform>();
		enttr->set_position({0, 10, 0});
		Camera *camera = entcam->add_component<Camera>();
		camera->set_width(window_width);
		camera->set_height(window_height);
		CameraController* cameracont = entcam->add_component<CameraController>();
        m_scene->add_object(entcam);
		m_renderer->set_camera(camera);

		Entity *ent2 = new Entity();
		ent2->add_component<Transform>()->set_position(glm::vec3(-2, 4, 0));
		ent2->add_component<Model>()->set_model("resources/cube-tex.obj");
        m_scene->add_object(ent2);

		Entity *entsound = new Entity();
		entsound->add_component<Transform>()->set_position(glm::vec3(-2, 4, 0));
		entsound->add_component<AudioSource>()->init("resources/sounds/corridor.wav", false, false, true);
        m_scene->add_object(entsound);

        font = new Font("resources/arial.ttf", 48);
        img = new UI_Image(Texture2D::blank, 0, 0, 10, 10);

		Entity *ent3 = new Entity();
		ent3->add_component<Transform>()->set_position({0, 5, 0});
		PointLight *l3 = ent3->add_component<PointLight>();
		l3->set_clq({0.f, 0.2f, 0.4f});
		m_scene->add_object(ent3);
        m_renderer->add_light(l3);

		Entity *ent4 = new Entity();
		ent4->add_component<Transform>()->set_position({-2, 5, 2});
		PointLight *l4 = ent4->add_component<PointLight>();
		l4->set_clq({0.f, 0.2f, 0.4f});
		m_scene->add_object(ent4);
        m_renderer->add_light(l4);

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



