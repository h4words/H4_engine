
#include <renderer/Renderer.hpp>
#include <components/Model.hpp>
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Log.hpp"
#include "Input.hpp"
#include <chrono>
#include <thread>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace H4_engine {
    Renderer::Renderer(Window *window)
        : m_window(window)
    {
    	LOG_INFO("Initializing Renderer");

        m_shader = new Shader("geometry");
        m_skybox_shader = new Shader("skybox");
        m_text_shader = new Shader("text");
        m_ui_shader = new Shader("ui");
        m_depth_shader = new Shader("shadow_depth");

        m_depthCubemaps = new CubemapArrayTexture(1024, 32);
        m_depthMaps = new ArrayTexture(1024, 32);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE); 
    }

    void Renderer::resize(int width, int height)
    {
        if (!m_camera) return;
        m_camera->set_width(width);
        m_camera->set_height(height);
    }

    void Renderer::render(double delta)
    {
        m_depthCubemaps->bind_framebuffer();
        glViewport(0, 0, m_depthCubemaps->get_resolution(), m_depthCubemaps->get_resolution());
        glClear(GL_DEPTH_BUFFER_BIT);

        int index = 0;
        for (Light *light : m_lights)
        {
            light->bind_depth(m_depth_shader, index++);
            EventRender eventRenderedDepth(this);
            MessageBus::Publish(eventRenderedDepth);
        }

        m_depthCubemaps->unbind_framebuffer();

        m_window->clear();

        glm::mat4 view_projection_matrix = m_camera->get_projection_matrix() * m_camera->get_view_matrix();
        m_shader->bind();
        m_shader->set_float("far_plane", 25.f);
        m_shader->set_int("nr_point_lights", 2);
        m_shader->set_vec3("viewPos", m_camera->get_entity()->get_component<Transform>()->get_position());
        index = 0;
        for (Light *light : m_lights)
        {
            light->bind(m_shader, index++);
        }
        m_shader->set_matrix4("view_projection_matrix", view_projection_matrix);
        m_depthCubemaps->bind(1);
        EventRender eventRendered(this);
        MessageBus::Publish(eventRendered);

        if (m_skybox)
        {
            m_skybox_shader->bind();
            glm::mat4 view = glm::mat4(glm::mat3(m_camera->get_view_matrix()));
            m_skybox_shader->set_matrix4("view", view);
            m_skybox_shader->set_matrix4("projection", m_camera->get_projection_matrix());
            m_skybox->render();
        }
    }
}
