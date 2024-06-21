#include <components/Light.hpp>
#include <Common.hpp>
#include <Log.hpp>
#include <components/Transform.hpp>

namespace H4_engine
{
	/*DirectionalLight::DirectionalLight(Entity *entity, glm::vec3 clq, glm::vec3 color)
		: Light(entity)
	{
		
	}

	void DirectionalLight::bind(Shader *s, int index)
	{
		s->set_vec3(("dirLights[" + std::to_string(index) + "].direction").c_str(), m_direction);
        s->set_vec3(("dirLights[" + std::to_string(index) + "].color").c_str(), m_color);
	}

	void DirectionalLight::bind_depth(Shader *depth_shader, int cubemap_index)
	{

	}*/

	PointLight::PointLight(Entity *entity)
		: Light(entity)
	{

	}

	void PointLight::bind(Shader *s, int index)
	{
		Transform *transform = m_entity->get_component<Transform>();
		s->set_vec3(("pointLights[" + std::to_string(index) + "].position").c_str(), transform->get_position());
        s->set_vec3(("pointLights[" + std::to_string(index) + "].color").c_str(), m_color);

		s->set_float(("pointLights[" + std::to_string(index) + "].constant").c_str(), m_clq.x);
		s->set_float(("pointLights[" + std::to_string(index) + "].linear").c_str(), m_clq.y);
        s->set_float(("pointLights[" + std::to_string(index) + "].quadratic").c_str(), m_clq.z);
		
		s->set_int(("pointLights[" + std::to_string(index) + "].depthMap_layer").c_str(), index);
	}

	void PointLight::bind_depth(Shader *depth_shader, int cubemap_index)
	{
		Transform *transform = m_entity->get_component<Transform>();
		float near_plane = 1.0f;
        float far_plane = 25.0f;
        glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.f, near_plane, far_plane);
        std::vector<glm::mat4> shadowTransforms;
        glm::vec3 lightPos = transform->get_position();
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
        
        depth_shader->bind();
		depth_shader->set_int("cubemap_index", cubemap_index);
        for (unsigned int i = 0; i < 6; ++i)
            depth_shader->set_matrix4(("shadowMatrices[" + std::to_string(i) + "]").c_str(), shadowTransforms[i]);
        depth_shader->set_float("far_plane", far_plane);
        depth_shader->set_vec3("lightPos", lightPos);
	}
	/*SpotLight::SpotLight(Entity *entity, glm::vec3 clq, glm::vec3 color)
		: Light(entity)
		, m_clq(clq)
	{
		
	}

	void SpotLight::bind(Shader *s, int index)
	{
		Transform *transform = m_entity->get_component<Transform>();
		s->set_vec3(("spotLights[" + std::to_string(index) + "].position").c_str(), transform->get_position());
		s->set_vec3(("spotLights[" + std::to_string(index) + "].direction").c_str(), transform->get_rotation());
        s->set_vec3(("spotLights[" + std::to_string(index) + "].color").c_str(), m_color);

		s->set_float(("spotLights[" + std::to_string(index) + "].constant").c_str(), m_clq.x);
		s->set_float(("spotLights[" + std::to_string(index) + "].linear").c_str(), m_clq.y);
        s->set_float(("spotLights[" + std::to_string(index) + "].quadratic").c_str(), m_clq.z);

		s->set_float(("spotLights[" + std::to_string(index) + "].cutOff").c_str(), glm::cos(glm::radians(12.5f)));
        s->set_float(("spotLights[" + std::to_string(index) + "].outerCutOff").c_str(), glm::cos(glm::radians(15.0f)));
	}
	
	void SpotLight::bind_depth(Shader *depth_shader, int cubemap_index)
	{

	}*/
}
