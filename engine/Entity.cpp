#include <Entity.hpp>

namespace H4_engine
{
    void Entity::tick()
    {
        for (Component *component : m_components)
        {
            component->tick();
        }
    }

    void Entity::process_new_components()
    {
        while (!m_first_frame_components.empty())
        {
            m_first_frame_components.front()->start();
            m_first_frame_components.pop();
        }
    }
    Component* Entity::add_component(std::string n)
    {
        auto iter = ComponentFactory::get().m_components.find(n);
        if (iter == ComponentFactory::get().m_components.end())
        {
            LOG_ERROR("Couldn't construct component with name {0}: no map entry", n);
            return 0;
        }
        Component *comp = (Component *)iter->second(this);
        m_components.push_back(comp);
        m_first_frame_components.push(comp);
        return comp;
    }
}
