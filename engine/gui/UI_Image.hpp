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

namespace H4_engine
{
	class UI_Image
	{
		public:
			UI_Image(Texture2D *texture, float x, float y, float width, float height);
			~UI_Image();
			void Render();
		private:
			VertexArray *m_vao;
            Texture2D *m_texture;
	};
}