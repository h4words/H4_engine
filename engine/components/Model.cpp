#include <components/Model.hpp>
#include <Common.hpp>
#include <Log.hpp>
#include <unordered_map>
#include <algorithm>
#include <vector>

#include <renderer/Texture2D.hpp>
#include <stb_image.h>

namespace H4_engine
{
	BufferLayout buffer_layout_vec3_vec2 
	{
		ShaderDataType::Float3,
		ShaderDataType::Float2,
		ShaderDataType::Float3
	};

	BEGIN_DATADESC(Model)
		DEFINE_FIELD(FIELD_STRING, m_model_path),
	END_DATADESC()

	Model::Model(Entity *entity)
		: Component(entity)
	{
		MessageBus::Subscribe<EventRender>(std::bind(&H4_engine::Model::on_update, this, std::placeholders::_1));
	}

	void Model::processNode(aiNode *node, const aiScene *scene, Material **materials)
	{
		for(unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
			if (mesh->mNumVertices <= 0) continue;
			m_VAOs.push_back(processMesh(mesh, scene, materials));	
		}
		for(unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, materials);
		}
	}  

	MeshVAO Model::processMesh(aiMesh *mesh, const aiScene *scene, Material **materials)
	{
		std::vector<Vertex> vertices;

		for(int i = 0; i < mesh->mNumVertices; i++)
		{
			glm::vec3 pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			glm::vec2 uv = glm::vec2(0);
			glm::vec3 normal = glm::vec3(0);
			if (mesh->HasNormals())
			{
				normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			}
			if (mesh->mTextureCoords[0])
			{
				uv = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}
			vertices.push_back(Vertex(pos, uv, normal));
		}
		MeshVAO meshVAO = MeshVAO(materials[mesh->mMaterialIndex]);
		VertexArray *vao = new VertexArray();
		meshVAO.set_vao(vao);
		VertexBuffer *mesh_vbo = new VertexBuffer(&vertices[0], sizeof(Vertex) * vertices.size(), buffer_layout_vec3_vec2);
		vao->add_buffer(*mesh_vbo);
		meshVAO.set_vertices_count(vertices.size());
		return meshVAO;
	}
	void Model::start()
	{
		if (!m_model_path.empty()) {
			set_model(m_model_path);
		}
	}
	void Model::set_model(std::string path) 
	{
		std::string base_dir = GetBaseDir(path) + "/";
		if (base_dir.empty())
		{
			base_dir = ".";
		}

		Transform *transform = m_entity->get_component<Transform>();
		m_model_matrix = GenerateModelMatrix(transform->get_position(), transform->get_scale());
		std::vector<aiString> textures;

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile( path, aiProcess_Triangulate);

		if (scene == nullptr) {
			LOG_ERROR(importer.GetErrorString());
		}

		Material* loaded_materials[scene->mNumMaterials];

		for (size_t m = 0; m < scene->mNumMaterials; m++)
		{
			aiMaterial* material = scene->mMaterials[m];
			Texture2D *diffuseTexture = Texture2D::blank;
			aiString str;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
			if (str.length > 0 && std::find(textures.begin(), textures.end(), str) == textures.end())
			{
				int w, h, comp;

				std::string diffuse_texname = std::string(str.C_Str());

				std::string texture_filename = diffuse_texname;
				if (!FileExists(texture_filename))
				{
					texture_filename = base_dir + diffuse_texname;
					if (!FileExists(texture_filename))
					{
						LOG_ERROR("Unable to find file: {0}", diffuse_texname);
						continue;
					}
				}

				unsigned char *image = stbi_load(texture_filename.c_str(), &w, &h, &comp, STBI_rgb_alpha);
				if (!image)
				{
					LOG_ERROR("Unable to load texture: {0}", texture_filename);
					continue;
				}
				diffuseTexture = new Texture2D(image, w, h, GL_RGBA);
				stbi_image_free(image);
				textures.push_back(str);
			}
			aiColor3D diffColor(0.f, 0.f, 0.f);
			material->Get(AI_MATKEY_COLOR_DIFFUSE, diffColor);
			Material *mat = new Material(diffuseTexture, glm::vec3(diffColor.r, diffColor.g, diffColor.b));
			loaded_materials[m] = mat;
		}

		processNode(scene->mRootNode, scene, loaded_materials);
	}

	void Model::on_update(EventRender &event)
	{
		if (m_VAOs.size() == 0) return;
		glDisable(GL_CULL_FACE); 
		glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		event.renderer->get_shader()->set_matrix4("model_matrix", m_model_matrix);
		event.renderer->get_depth_shader()->set_matrix4("model", m_model_matrix);
		for (MeshVAO &mesh : m_VAOs)
		{
			mesh.get_material()->bind();
			mesh.get_vao()->bind();
			glDrawArrays(GL_TRIANGLES, 0, mesh.get_vertices_count());
		}
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE); 
	}
}
