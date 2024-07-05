#pragma once
#include <vector>
#include <Entity.hpp>

namespace H4_engine
{
	class Entity;
	class Scene
	{
		public:
			std::vector<Entity*> get_objects();
			void add_object(Entity* obj);
			void purge();
		private:
			std::vector<Entity*> m_objects;
	};
}
