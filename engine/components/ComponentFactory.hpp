#pragma once
#include <map>
#include <string>
#include <Log.hpp>
#include <Entity.hpp>

namespace H4_engine
{
    class Entity;
    
    template <class T>
    void* constructor(Entity *entity)
    {
        return (void*)new T(entity);
    }
    
    struct ComponentFactory
    {
        typedef void* (*constructor_t)(Entity*);
        std::map<std::string, constructor_t> m_components;

        template <class T>
        void register_class(std::string const &n)
        {
            m_components.insert(std::make_pair(n, &constructor<T>));
        }
    };

    static ComponentFactory component_factory;

    //2 weeks triumph - seems to understand source engine code now
    #define REGISTER_COMPONENT(n)                           \
        class n##Factory                                    \
        {                                                   \
        public:                                             \
            n##Factory()                                    \
            {                                               \
                component_factory.register_class<n>(#n);    \
            }                                               \
        };                                                  \
        static n##Factory n##FactoryFoo;
}