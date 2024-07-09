#pragma once
#include <Common.hpp>
#include <components/Component.hpp>
#include <vector>
#include <renderer/Shader.hpp>
#include <renderer/Cubemap.hpp>
#include <renderer/FrameBuffer.hpp>

namespace H4_engine
{
	class Light : public Component
	{
		public:
			DECLARE_DATADESC()
			Light(Entity *entity)
				: Component(entity) { };
			void start();
			void set_color(glm::vec3 color) { m_color = color; }
            virtual void bind(Shader *s, int index) = 0;
			virtual void bind_depth(Shader *s, int cubemap_index) = 0;
        protected:
            glm::vec3 m_color = {1.f, 1.f, 1.f};
	};
    /*class DirectionalLight : public Light
	{
		public:
			DirectionalLight(Entity *entity
						   , glm::vec3 direction = {0.f, 0.f, 0.f}
                           , glm::vec3 color = {1.f, 1.f, 1.f});
			void bind(Shader *s, int index);
			void bind_depth(Shader *s, int cubemap_index);
		private:
            glm::vec3 m_direction;
	};*/
    class PointLight : public Light
	{
		public:
			DECLARE_COMPONENT(PointLight)
			DECLARE_DATADESC()
			PointLight(Entity *entity);
			void set_clq(glm::vec3 clq) { m_clq = clq; }
			void bind(Shader *s, int index);
			void bind_depth(Shader *s, int cubemap_index);
		private:
			glm::vec3 m_clq;
	};
	REGISTER_COMPONENT(PointLight);
	
    /*class SpotLight : public Light
	{
		public:
			SpotLight(Entity *entity
                    , glm::vec3 clq = {0, 0, 1}
                    , glm::vec3 color = {1.f, 1.f, 1.f});
			void bind(Shader *s, int index);
			void bind_depth(Shader *s, int cubemap_index);
		private:
			glm::vec3 m_clq;
	};*/
}
