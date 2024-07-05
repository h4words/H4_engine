#pragma once
#include <map>
#include <string>
#include <Log.hpp>
#include <systems/BaseGameSystem.hpp>

namespace H4_engine
{   
    template <class T>
    void* constructor()
    {
        return (void*)new T();
    }
    
    struct GameSystemFactory
    {
        typedef void* (*constructor_t)();
        std::map<std::string, constructor_t> m_components;

        template <class T>
        void register_class(std::string const &n)
        {
            m_components.insert(std::make_pair(n, &constructor<T>));
        }
    };

    static GameSystemFactory gamesystem_factory;

    #define REGISTER_SYSTEM(n)                              \
        class n##Factory                                    \
        {                                                   \
        public:                                             \
            n##Factory()                                    \
            {                                               \
                gamesystem_factory.register_class<n>(#n);   \
            }                                               \
        };                                                  \
        static n##Factory n##FactoryFoo;
}