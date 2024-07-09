#ifdef MAP_EDITOR
#include <mapeditor/MapEditor.hpp>
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <Entity.hpp>
#include <components/ComponentFactory.hpp>
#include <map/MapUtils.hpp>

namespace H4_engine
{
    int MapEditor::start(unsigned int window_width, unsigned int window_height)
    {
        m_Window = new Window("map_editor", window_width, window_height);
        LOG_INFO("Fully initialized.");

        std::vector<Entity *> entities;

        std::vector<std::string> components;
        for (auto it = ComponentFactory::get().m_components.begin(); it != ComponentFactory::get().m_components.end(); ++it)
        {
            components.push_back(it->first);
        }

        std::string path;
        
        while (!m_Window->shouldClose())
        {
            m_Window->poll_events();

            m_Window->clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
            ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

            ImGui::Begin("editor", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

            int i = 0;
            for (auto it=entities.begin(); it!=entities.end();)
            {
                Entity *ent = *it;
                std::string s = "Entity " + std::to_string(i++);
                if (ImGui::TreeNode(s.c_str()))
                {
                    std::vector<Component*> comps = ent->get_all_components();
                    for (auto c_it=comps.begin(); c_it!=comps.end();)
                    {
                        Component *comp = *c_it;
                        std::string comp_id = "##" + std::to_string(reinterpret_cast<uintptr_t>(comp));
                        if (ImGui::TreeNode((comp->GetName() + comp_id).c_str()))
                        {
                            DataMap *datamap = comp->GetDataDescMap();
                            while (datamap != NULL)
                            {
                                if (datamap->fields_count > 0 && datamap->component_name != comp->GetName())
                                {
                                    ImGui::Text(("Derived from " + datamap->component_name).c_str());
                                }
                                for (int field_dm_i = 0; field_dm_i < datamap->fields_count; field_dm_i++)
                                {
                                    FieldInfo field_info = datamap->fields[field_dm_i];
                                    switch (field_info.fieldtype)
                                    {
                                        case FIELD_STRING:
                                        {
                                            ImGui::InputText((field_info.alias + comp_id).c_str(), (std::string *)(((char *)comp) + field_info.offset));
                                            break;
                                        }
                                        case FIELD_BOOLEAN:
                                        {
                                            ImGui::Checkbox((field_info.alias + comp_id).c_str(), (bool *)(((char *)comp) + field_info.offset));
                                            break;
                                        }
                                        case FIELD_INTEGER:
                                        {
                                            ImGui::InputInt((field_info.alias + comp_id).c_str(), (int *)(((char *)comp) + field_info.offset));
                                            break;
                                        }
                                        case FIELD_FLOAT:
                                        {
                                            ImGui::InputFloat((field_info.alias + comp_id).c_str(), (float *)(((char *)comp) + field_info.offset));
                                            break;
                                        }
                                        case FIELD_VECTOR:
                                        {
                                            ImGui::InputFloat3((field_info.alias + comp_id).c_str(), (float *)(((char *)comp) + field_info.offset));
                                            break;
                                        }
                                        case FIELD_COLOR:
                                        {
                                            ImGui::ColorEdit3((field_info.alias + comp_id).c_str(), (float *)(((char *)comp) + field_info.offset));
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                                datamap = datamap->base_map;
                            }
                            if (ImGui::Button(("Delete " + comp->GetName() + comp_id).c_str()))
                            {
                                ent->delete_component(comp);
                                c_it--;
                            }
                            ImGui::TreePop();
                        }
                        c_it++;
                    }
                    ImGui::TreePop();
                    if (ImGui::BeginCombo(("##AddComponentTo" + s).c_str(), "Add Component"))
                    {
                        std::string current_item = "";
                        for (std::string component : components)
                        {
                            bool is_selected = (current_item == component);
                            if (ImGui::Selectable(component.c_str(), is_selected))
                                current_item = component;
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                        }
                        if (!current_item.empty())
                        {
                            ent->add_component(current_item);
                            current_item.clear();
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(("Delete " + s).c_str()))
                    {
                        entities.erase(it);
                        it--;
                        delete ent;
                    }
                }
                it++;
                ImGui::Separator();
            }
            if (ImGui::Button("Add Entity"))
                entities.push_back(new Entity());
            ImGui::SameLine();
            ImGui::Text("entities = %d", entities.size());

            ImGui::InputText("Map Path", &path);

            if (ImGui::Button("Save"))
            {
                MapWriter writer;
                writer.set_entities(entities);
                writer.write(path);
            }
            ImGui::SameLine();
            if (ImGui::Button("Load"))
            {
                MapLoader loader;
                loader.load(path);
                entities = loader.get_loaded_entities();
            }

            ImGui::End();

            m_Window->render();
        }
        LOG_INFO("Exited main loop.");
        return 0;
    }
}
#endif