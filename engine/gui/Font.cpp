#include "Font.hpp"
#include <glad/glad.h>
#include <Log.hpp>
#include <stb_image.h>
#include <renderer/Shader.hpp>
namespace H4_engine
{
    FT_Library Font::ft = nullptr;
    BufferLayout buffer_layout_vec4{ShaderDataType::Float2, ShaderDataType::Float2};
    Font::Font(std::string path, unsigned int size)
    {
        if (ft == nullptr)
            if (FT_Init_FreeType(&ft))
                LOG_ERROR("FREETYPE: Could not init FreeType Library");
        
        // Load font as face
        FT_Face face;
        if (FT_New_Face(ft, path.c_str(), 0, &face))
            LOG_ERROR("FREETYPE: Failed to load font");

        // Set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, size);

        // Load first 128 characters of ASCII set
        for (int c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                LOG_ERROR("FREETYTPE: Failed to load Glyph");
                continue;
            }
            Character character = {
                new Texture2D(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED),
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        m_vao = new VertexArray();
		m_vbo = new VertexBuffer(NULL, sizeof(float) * 6 * 4, buffer_layout_vec4, VertexBuffer::EUsage::Dynamic);
		m_vao->add_buffer(*m_vbo);
    }
    Font::~Font()
    {
        
    }
    void Font::RenderText(Shader *textShader, std::string text, float x, float y, float scale, glm::vec3 color)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        textShader->set_vec3("textColor", color);

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = Characters[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // Update VBO for each character
            float vertices[24] = {
                xpos + w, ypos + h, 1.0, 0.0,
                xpos, ypos + h, 0.0, 0.0,
                xpos, ypos, 0.0, 1.0,
                xpos, ypos, 0.0, 1.0,
                xpos + w, ypos, 1.0, 1.0,
                xpos + w, ypos + h, 1.0, 0.0
            };
            // Render glyph texture over quad
            ch.texture->bind(0);
            // Update content of VBO memory
            m_vbo->buffer(&vertices, sizeof(vertices));
            m_vao->bind();
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glDisable(GL_BLEND);
    }
}