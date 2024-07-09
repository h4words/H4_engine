#include <renderer/Window.hpp>
#include <components/Model.hpp>
#include "renderer/Shader.hpp"
#include "components/Camera.hpp"
#include "Log.hpp"
#include "Input.hpp"
#include <chrono>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace H4_engine {

    Window::Window(std::string title, int width, int height, int flags)
    	: m_data({ std::move(title), width, height })
        , m_flags(flags)
    {
    	LOG_INFO("Constructing window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.height);
        int resultCode = init();
    }

    Window::~Window()
    {
    	LOG_INFO("Destructing window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.height);
        shutdown();
    }
    
    int Window::init()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    	LOG_INFO("Creating window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.height);
        m_pWindow = SDL_CreateWindow(m_data.title.c_str(), m_data.width * 0.5, m_data.height * 0.2, m_data.width, m_data.height, SDL_WINDOW_OPENGL | m_flags);
        m_pGLcontext = SDL_GL_CreateContext(m_pWindow);
        
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        {
            LOG_CRITICAL("Failed to initialize GLAD");
            return -3;
        }

    #ifdef IMGUI_AVAILABLE
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui_ImplSDL2_InitForOpenGL(m_pWindow, m_pGLcontext);
        ImGui_ImplOpenGL3_Init();
    #endif

        stbi_set_flip_vertically_on_load(true);

        int w; int h; int comp;
		auto* data = stbi_load("resources/blank.png", &w, &h, &comp, STBI_rgb);
		Texture2D::blank = new Texture2D(data, w, h);
        stbi_image_free(data);

        return 0;
    }

    void Window::shutdown()
    {
        SDL_GL_DeleteContext(m_pGLcontext);
    }

    SDL_Event event;
    void Window::poll_events()
    {
        Input::ScrollMouse(0);
        while( SDL_PollEvent( &event ) )
        {
        #ifdef IMGUI_AVAILABLE
            ImGui_ImplSDL2_ProcessEvent(&event);
        #endif
            switch( event.type ){
                case SDL_KEYDOWN:
                {
                    Input::PressKey(static_cast<KeyCode>(event.key.keysym.scancode));
                    EventKeyPressed eventPressed(static_cast<KeyCode>(event.key.keysym.scancode), false);
                    MessageBus::Publish(eventPressed);
                    break;
                }
                case SDL_KEYUP:
                {
                    Input::ReleaseKey(static_cast<KeyCode>(event.key.keysym.scancode));
                    EventKeyReleased eventReleased(static_cast<KeyCode>(event.key.keysym.scancode));
                    MessageBus::Publish(eventReleased);
                    break;
                }
                case SDL_QUIT:
                    m_shouldClose = true;
                    break;
                case SDL_MOUSEMOTION:
                {
                    SDL_GetGlobalMouseState(&m_mouseX,&m_mouseY);
                    EventMouseMoved eventMoved(m_mouseX, m_mouseY);
                    MessageBus::Publish(eventMoved);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    Input::PressMouseButton(static_cast<MouseButton>(event.button.button));
                    EventMouseButtonPressed eventReleased(static_cast<MouseButton>(event.button.button), event.button.x, event.button.y);
                    MessageBus::Publish(eventReleased);
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    Input::ReleaseMouseButton(static_cast<MouseButton>(event.button.button));
                    EventMouseButtonReleased eventReleased(static_cast<MouseButton>(event.button.button), event.button.x, event.button.y);
                    MessageBus::Publish(eventReleased);
                    break;
                }
                case SDL_MOUSEWHEEL:
                {
                    Input::ScrollMouse(event.wheel.y);
                    EventMouseScroll eventScrolled(event.wheel.y);
                    MessageBus::Publish(eventScrolled);
                    break;
                }
                case SDL_WINDOWEVENT:
                {
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        m_data.width = event.window.data1;
                        m_data.height = event.window.data2;

                        EventWindowResize eventResized(m_data.width, m_data.height);
                        MessageBus::Publish(eventResized);
                    }
                    break;
                }
            }
        }
    }
}