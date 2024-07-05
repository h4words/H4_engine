#include <map/MapLoader.hpp>

namespace H4_engine
{
    void MapLoader::load(std::string filename, Scene* scene)
    {
        m_stream = new std::ifstream(filename, std::ios::in | std::ios::binary);
        uint32_t identifier;
        ReadSimple(identifier);
        if (identifier != MAPIDHEADER)
        {
            LOG_ERROR("{0} is not H4_engine map!", filename);
        }
        uint16_t entities_num;
        ReadSimple(entities_num);
        LOG_INFO("{0} entities", entities_num);
        for(uint16_t ent_i = 0; ent_i < entities_num; ent_i++)
        {
            Entity *ent = new Entity();
            uint16_t components_num;
            ReadSimple(components_num);
            LOG_INFO("{0} components", components_num);
            for(uint16_t comp_i = 0; comp_i < components_num; comp_i++)
            {
                std::string component_name;
                ReadStr(component_name);
                LOG_INFO("{0} component", component_name);
                Component* component = ent->add_component(component_name);
                uint8_t fields_num;
                ReadSimple(fields_num);
                LOG_INFO("{0} fields", fields_num);
                for (uint8_t field_i = 0; field_i < fields_num; field_i++)
                {
                    std::string field_name;
                    ReadStr(field_name);
                    DataMap *datamap = component->GetDataDescMap();
                    FieldInfo field_info;
                    for (int field_dm_i = 0; field_dm_i < datamap->fields_count; field_dm_i++)
                    {
                        if (datamap->fields[field_dm_i].alias == field_name)
                        {
                            field_info = datamap->fields[field_dm_i];
                            break;
                        }
                    }
                    std::string field;
                    std::string* str_field = nullptr;
                    switch(field_info.fieldtype)
                    {
                        case FIELD_STRING:
                        {
                            ReadStr(field);
                            str_field = (std::string*)(((char*)component) + field_info.offset);
                            *str_field = field;
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            scene->add_object(ent);
        }
        m_stream->close();
    }

    void MapLoader::ReadStr(std::string &dest)
    {
        uint8_t size;
        m_stream->read((char*)&size, sizeof(size));
        dest.resize(size);
        m_stream->read(dest.data(), size);
    }

    void MapLoader::ReadStr(std::string &dest, uint8_t &size)
    {
        m_stream->read((char*)&size, sizeof(uint8_t));
        dest.resize(size);
        m_stream->read(dest.data(), size);
    }
    
    template<typename T>
    void MapLoader::ReadSimple(T &dest)
    {
        m_stream->read((char*)&dest, sizeof(T));
    }
}