
#include "UI_Image.hpp"
#include <glad/glad.h>
#include <Log.hpp>
#include <stb_image.h>
#include <renderer/Shader.hpp>
#include <Common.hpp>
#include <vector>
namespace H4_engine
{
    BufferLayout buffer_layout_vec3_vec2_ui{ShaderDataType::Float3, ShaderDataType::Float2};
    UI_Image::UI_Image(Texture2D *texture, float x, float y, float width, float height)
        : m_texture(texture)
    {
        m_vao = new VertexArray();

        float w = x + width;
        float h = y + height;

        std::vector<Triangle> ts = {Triangle(Vertex(glm::vec3(x, y, 0), glm::vec2(0, 0)), Vertex(glm::vec3(w, y, 0), glm::vec2(1, 0)), Vertex(glm::vec3(x, h, 0), glm::vec2(0, 1))),
                                    Triangle(Vertex(glm::vec3(w, h, 0), glm::vec2(1, 1)), Vertex(glm::vec3(w, y, 0), glm::vec2(1, 0)), Vertex(glm::vec3(x, h, 0), glm::vec2(0, 1)))};

        VertexBuffer *m_vbo = new VertexBuffer(&ts[0], sizeof(Triangle) * ts.size(), buffer_layout_vec3_vec2_ui);
        m_vao->add_buffer(*m_vbo);
    }
    UI_Image::~UI_Image()
    {
        
    }
    void UI_Image::Render()
    {
        m_texture->bind(0);
        m_vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}