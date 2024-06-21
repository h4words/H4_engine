#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <Common.hpp>
#include <renderer/Material.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Log.hpp>
#include <vector>
#include <renderer/Texture2D.hpp>
#include <renderer/VertexArray.hpp>
namespace H4_engine
{
	class MeshVAO
	{
		public:
			MeshVAO(Material *material) 
				: m_material(material) { }
			VertexArray* get_vao() { return m_vao; };
			void set_vao(VertexArray *vao) { m_vao = vao; };
			void set_vertices_count(unsigned int count) { m_vertices_count = count; }
			unsigned int get_vertices_count() { return m_vertices_count; }
			Material* get_material() { return m_material; }
		private:
			VertexArray *m_vao;
			Material *m_material;
			unsigned int m_vertices_count;
	};
}