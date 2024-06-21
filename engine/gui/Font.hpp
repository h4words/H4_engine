#pragma once
#include <glm/glm.hpp>
#include <string>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <map>
#include <renderer/Texture2D.hpp>
#include <renderer/VertexArray.hpp>
#include <renderer/Shader.hpp>

namespace H4_engine
{
    struct Character {
        Texture2D *texture;
        glm::vec2 Size;
        glm::vec2 Bearing;
        long int Advance;
    };

	class Font
	{
		public:
			Font(std::string path, unsigned int size);
			~Font();
			void RenderText(Shader *textShader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
		private:
			VertexArray *m_vao;
			VertexBuffer *m_vbo;
            static FT_Library ft;
            std::map<char, Character> Characters;
	};
}