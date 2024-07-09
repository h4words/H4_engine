#include <map/MapUtils.hpp>

namespace H4_engine
{
    void MapLoader::load(std::string filename)
    {
        m_stream = new std::ifstream(filename, std::ios::in | std::ios::binary);
        if (!Identify())
        {
            LOG_ERROR("{0} is not H4_engine map!", filename);
            return;
        }
        std::size_t entities_num;
        ReadSimple(entities_num);
        for (std::size_t ent_i = 0; ent_i < entities_num; ent_i++)
        {
            Entity *ent = new Entity();
            std::size_t components_num;
            ReadSimple(components_num);
            for (std::size_t comp_i = 0; comp_i < components_num; comp_i++)
            {
                ReadComponent(ent);
            }
            m_ents.push_back(ent);
        }
        m_stream->close();
    }

    void MapLoader::ReadStr(std::string &dest)
    {
        std::size_t size;
        m_stream->read((char *)&size, sizeof(size));
        dest.resize(size);
        m_stream->read(dest.data(), size);
    }

    void MapLoader::ReadStr(std::string &dest, std::size_t &size)
    {
        m_stream->read((char *)&size, sizeof(std::size_t));
        dest.resize(size);
        m_stream->read(dest.data(), size);
    }

    template <typename T>
    void MapLoader::ReadSimple(T &dest)
    {
        m_stream->read((char *)&dest, sizeof(T));
    }

    void MapLoader::ReadComponent(Entity *ent)
    {
        std::string component_name;
        ReadStr(component_name);
        Component *component = ent->add_component(component_name);
        unsigned int fields_num;
        ReadSimple(fields_num);
        for (unsigned int field_i = 0; field_i < fields_num; field_i++)
        {
            std::string field_name;
            ReadStr(field_name);
            DataMap *datamap = component->GetDataDescMap();
            FieldInfo field_info = FindFieldByName(field_name, datamap);
            ReadField(field_info, ((char *)component) + field_info.offset);
        }
    }

    FieldInfo MapLoader::FindFieldByName(std::string name, DataMap *datamap)
    {
        while (datamap != NULL)
        {
            for (unsigned int field_dm_i = 0; field_dm_i < datamap->fields_count; field_dm_i++)
            {
                if (datamap->fields[field_dm_i].alias == name)
                {
                    return datamap->fields[field_dm_i];
                }
            }
            datamap = datamap->base_map;
        }
        return {};
    }

    void MapLoader::ReadField(FieldInfo field_info, void *dest)
    {
        std::string field;
        bool b_field = false;
        switch (field_info.fieldtype)
        {
        case FIELD_STRING:
        {
            ReadStr(field);
            *(std::string *)(dest) = field;
            break;
        }
        case FIELD_BOOLEAN:
        {
            ReadSimple(b_field);
            *(bool *)(dest) = b_field != 0;
            break;
        }
        case FIELD_INTEGER:
        {
            ReadSimple(*(int *)(dest));
            break;
        }
        case FIELD_FLOAT:
        {
            ReadSimple(*(float *)(dest));
            break;
        }
        case FIELD_VECTOR:
        case FIELD_COLOR:
        {
            ReadSimple(*(glm::vec3 *)(dest));
            break;
        }
        default:
            break;
        }
    }

    bool MapLoader::Identify()
    {
        uint32_t identifier;
        ReadSimple(identifier);
        return identifier == MAPIDHEADER;
    }

    void MapLoader::push_to_scene(Scene *scene)
    {
        for (Entity *ent : m_ents)
        {
            scene->add_object(ent);
        }
    }
    std::vector<Entity *> MapLoader::get_loaded_entities()
    {
        return m_ents;
    }

    ///////////////////////////////////////////////////////

    void MapWriter::write(std::string filename)
    {
        m_stream = new std::ofstream(filename, std::ios::out | std::ios::binary);
        WriteSimple(MAPIDHEADER);
        WriteSimple(m_ents.size());
        for (Entity *ent : m_ents)
        {
            WriteSimple(ent->get_all_components().size());
            for (Component *component : ent->get_all_components())
            {
                WriteComponent(component);
            }
        }
        m_stream->close();
    }

    void MapWriter::WriteComponent(Component *component)
    {
        WriteStr(component->GetName());
        DataMap *datamap = component->GetDataDescMap();
        unsigned int count = 0;
        while (datamap != NULL)
        {
            count += datamap->fields_count;
            datamap = datamap->base_map;
        }
        datamap = component->GetDataDescMap();
        WriteSimple(count);
        while (datamap != NULL)
        {
            for (unsigned int field_i = 0; field_i < datamap->fields_count; field_i++)
            {
                FieldInfo field_info = datamap->fields[field_i];
                WriteStr(field_info.alias);
                WriteField(field_info, ((char *)component) + field_info.offset);
            }
            datamap = datamap->base_map;
        }
    }

    void MapWriter::WriteField(FieldInfo field_info, void *dest)
    {
        std::string field;
        switch (field_info.fieldtype)
        {
        case FIELD_STRING:
        {
            WriteStr(*(std::string *)dest);
            break;
        }
        case FIELD_BOOLEAN:
        {
            WriteSimple(*(bool *)dest != 0);
            break;
        }
        case FIELD_INTEGER:
        {
            WriteSimple(*(int *)dest);
            break;
        }
        case FIELD_FLOAT:
        {
            WriteSimple(*(float *)dest);
            break;
        }
        case FIELD_VECTOR:
        case FIELD_COLOR:
        {
            WriteSimple(*(glm::vec3 *)dest);
            break;
        }
        default:
            break;
        }
    }

    void MapWriter::set_entities(std::vector<Entity *> ents)
    {
        m_ents = ents;
    }

    void MapWriter::WriteStr(std::string dest)
    {
        std::size_t size = dest.size();
        m_stream->write((char *)&size, sizeof(std::size_t));
        m_stream->write(dest.data(), dest.size());
    }

    template <typename T>
    void MapWriter::WriteSimple(T dest)
    {
        m_stream->write((char *)&dest, sizeof(T));
    }
}