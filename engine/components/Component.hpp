#pragma once
#include <Entity.hpp>
#include <components/DataDesc.hpp>
namespace H4_engine
{
	class Entity;
	class Component
	{
		public:
			Component(Entity *entity)
				: m_entity(entity) { };
			DECLARE_DATADESC();
			virtual void start() { };
			virtual void tick() { };
			Entity* get_entity() { return m_entity; }
		protected:
			Entity *m_entity;
	};
}
