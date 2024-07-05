#pragma once
#include <string>
#include <Scene.hpp>
#include <fstream>
#include <components/DataDesc.hpp>

// little-endian "H4MP"
#define MAPIDHEADER (('P' << 24) + ('M' << 16) + ('4' << 8) + 'H')

namespace H4_engine
{
    class MapLoader
    {
        public:
            MapLoader() { };
            void load(std::string filename, Scene* scene);
        private:
            std::ifstream *m_stream;
            void ReadStr(std::string &dest);
            void ReadStr(std::string &dest, uint8_t &size);
            template<typename T>
            void ReadSimple(T &dest);
    };
}