#ifdef MAP_EDITOR
#pragma once
#include <renderer/Window.hpp>

namespace H4_engine
{
    class MapEditor
    {
        public:
            MapEditor() { };
            int start(unsigned int window_width, unsigned int window_height);
        private:
            void InputVector(const char* c, glm::vec3 vec);
            Window* m_Window;
            std::ofstream *m_stream;
            void WriteStr(std::string dest);
            template<typename T>
            void WriteSimple(T dest);

    };
}
#endif