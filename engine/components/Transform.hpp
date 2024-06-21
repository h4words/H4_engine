#pragma once
#include <Common.hpp>
#include <components/Component.hpp>
#include <vector>
#include <functional>
#include <Log.hpp>

namespace H4_engine
{
	class Transform : public Component
	{
		public:
			Transform(Entity *entity)
                    : Component(entity) { };

            glm::vec3 get_position() { return m_position; }
            glm::vec3 get_rotation() { return m_rotation; }
            glm::vec3 get_scale() { return m_scale; }

            void set_position(glm::vec3 position) 
            { 
                for (auto func : m_position_callbacks)
                {
                    func(m_position, position);
                }
                m_position = position; 
            }
            void set_rotation(glm::vec3 rotation) 
            {
                for (auto func : m_rotation_callbacks)
                {
                    func(m_rotation, rotation);
                }
                m_rotation = rotation;
            }
            void set_scale(glm::vec3 scale) 
            { 
                m_scale = scale; 
            }

            void add_position_callback(std::function<void(const glm::vec3 old, const glm::vec3 now)> cb)
            {
                m_position_callbacks.push_back(cb);
            }

            void add_rotation_callback(std::function<void(const glm::vec3 old, const glm::vec3 now)> cb)
            {
                m_rotation_callbacks.push_back(cb);
            }

        private:
            glm::vec3 m_position = {0.f, 0.f, 0.f};
            glm::vec3 m_rotation = {0.f, 0.f, 0.f};
            glm::vec3 m_scale = {1.f, 1.f, 1.f};

            std::vector<std::function<void(const glm::vec3 old, const glm::vec3 now)>> m_position_callbacks;
            std::vector<std::function<void(const glm::vec3 old, const glm::vec3 now)>> m_rotation_callbacks;
	};
    REGISTER_COMPONENT(Transform);
}