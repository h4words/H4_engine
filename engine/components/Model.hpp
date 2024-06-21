#pragma once
#include <Common.hpp>
#include <components/Component.hpp>
#include <vector>
#include <Event.hpp>
#include <components/Transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <renderer/MeshVAO.hpp>
#include <renderer/VertexArray.hpp>
#include <renderer/VertexBuffer.hpp>
namespace H4_engine
{
	class Model : public Component
	{
		public:
			Model(Entity *entity);
			void set_model(std::string path);
			void on_update(EventRender &event);
		private:
			void processNode(aiNode *node, const aiScene *scene, Material **materials);
			MeshVAO processMesh(aiMesh *mesh, const aiScene *scene, Material **materials);
			std::vector<MeshVAO> m_VAOs;
			glm::mat4 m_model_matrix;
	};
	REGISTER_COMPONENT(Model);
}
