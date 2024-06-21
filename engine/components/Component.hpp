#pragma once
#include <Entity.hpp>

namespace H4_engine
{
	class Entity;
	class Component
	{
		public:
			Component(Entity *entity)
				: m_entity(entity) { }
			virtual void start() { };
			virtual void tick() { };
			Entity* get_entity() { return m_entity; }
		protected:
			Entity *m_entity;
	};
}
