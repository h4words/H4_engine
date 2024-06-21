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
}
