#pragma once

#include <glad/glad.h>
#include <Log.hpp>

namespace H4_engine
{
	class Texture
	{
		public:
			Texture() {};
			~Texture() {};
			unsigned int get_id() { return m_id; }
			virtual void bind(unsigned int unit = 0) = 0;
			virtual void unbind(unsigned int unit = 0) = 0;
		protected:
			unsigned int m_id;
	};
}