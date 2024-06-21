#pragma once

#include <glad/glad.h>
#include <Log.hpp>
#include <renderer/Texture.hpp>

namespace H4_engine
{
	class Texture2D : Texture
	{
		public:
			Texture2D(const unsigned char* data, unsigned int width, unsigned int height, GLenum comp=GL_RGB);
			~Texture2D();
			void bind(unsigned int unit);
			void unbind(unsigned int unit);
			static Texture2D *blank;
		private:
			unsigned int m_width;
			unsigned int m_height;
	};
}