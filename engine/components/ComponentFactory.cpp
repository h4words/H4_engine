#include <components/ComponentFactory.hpp>

namespace H4_engine
{
    ComponentFactory& ComponentFactory::get()
    {
        static ComponentFactory instance;
        return instance;
    }
}