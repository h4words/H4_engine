#pragma once

#include <Common.hpp>
#include <renderer/Cubemap.hpp>
#include <renderer/VertexArray.hpp>
#include <renderer/VertexBuffer.hpp>
#include <vector>
#include <renderer/MeshVAO.hpp>

namespace H4_engine
{
	class Skybox
	{
		public:
			Skybox(Cubemap *cubemap);
			void render();
		private:
            Cubemap *m_cubemap;
			VertexArray *m_vao;
	};
}
