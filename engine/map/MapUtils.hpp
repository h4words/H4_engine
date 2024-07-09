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
            void load(std::string filename);
            void push_to_scene(Scene* scene);
            std::vector<Entity*> get_loaded_entities();
        private:
            std::ifstream *m_stream;
            std::vector<Entity*> m_ents;
            FieldInfo FindFieldByName(std::string name, DataMap *datamap);
            bool Identify();
            void ReadComponent(Entity *ent);
            void ReadField(FieldInfo field_info, void* dest);
            void ReadStr(std::string &dest);
            void ReadStr(std::string &dest, std::size_t &size);
            template<typename T>
            void ReadSimple(T &dest);
    };
    class MapWriter
    {
        public:
            MapWriter() { };
            void write(std::string filename);
            void set_entities(std::vector<Entity*> ents);
        private:
            std::ofstream *m_stream;
            std::vector<Entity*> m_ents;
            void WriteComponent(Component *component);
            void WriteField(FieldInfo field_info, void* dest);
            void WriteStr(std::string dest);
            template<typename T>
            void WriteSimple(T dest);
    };
}