#include "Scene.hpp"

namespace H4_engine
{
	std::vector<Entity*> Scene::get_objects()
	{
		return m_objects;
	}
	void Scene::add_object(Entity* obj)
	{
		m_objects.push_back(obj);
	}
	void Scene::purge()
	{
		for (Entity *ent : m_objects)
		{
			delete ent;
		}
		m_objects.clear();
	}
}
