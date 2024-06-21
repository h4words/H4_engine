#pragma once

#include <glad/glad.h>
#include <Log.hpp>
#include <vector>
#include <stb_image.h>
#include <renderer/Texture.hpp>
namespace H4_engine
{
	class Cubemap : Texture
	{
		public:
			Cubemap(std::vector<std::string> faces);
			Cubemap();
			~Cubemap();
			void bind(unsigned int unit);
			void unbind(unsigned int unit);
		private:
			unsigned int m_width;
			unsigned int m_height;
	};
}