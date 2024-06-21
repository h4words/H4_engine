#pragma once
#include <glm/glm.hpp>
#include <components/Component.hpp>
#include <vector>
#include <queue>
#include <components/ComponentFactory.hpp>

namespace H4_engine
{
	class Component;
	class Entity
	{
	public:
		Entity() { };
		Entity(std::vector<Component*> components)
			: m_components(components) { };

		template <typename T>
		T *get_component()
		{
			for (Component *component : m_components)
			{
				if (dynamic_cast<T*>(component) != nullptr)
				{
					return dynamic_cast<T*>(component);
				}
			}
			return nullptr;
		}

		// template<typename T>
		// std::vector<T> get_all_components();

		template <typename T>
		T* add_component()
		{
			T* component = new T(this);
			m_components.push_back(component);
			m_first_frame_components.push(component);
			return component;
		}

		void* add_component(std::string const &n)
        {
            auto iter = component_factory.m_components.find(n);
            if (iter == component_factory.m_components.end())
            {
                LOG_ERROR("Couldn't construct component with name {0}: no map entry", n);
                return 0;
            }
            return iter->second(this);
        }

		void process_new_components();
		void tick();
	private:
		std::queue<Component*> m_first_frame_components;
		std::vector<Component*> m_components;
	};
}
