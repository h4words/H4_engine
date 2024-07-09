#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <components/Transform.hpp>

namespace H4_engine {

    class Camera : public Component
    {
        public:
            DECLARE_COMPONENT(Camera);
            Camera(Entity *entity);

            void start();

            void set_height(float height) { m_screen_height = height; m_update_projection_matrix = true; };
            void set_width(float width) { m_screen_width = width; m_update_projection_matrix = true; };
            void set_clipping_plane( float amount);
            void set_aspect(float aspect);
            glm::mat4 get_view_matrix();
            glm::mat4 get_projection_matrix();

            void move_forward( float delta);
            void move_right( float delta);
            void move_up( float delta);

            void add_movement_and_rotation( glm::vec3 movement_delta,
                                            glm::vec3 rotation_delta);
        private:
            bool m_update_projection_matrix = false;
            float m_screen_height = 600;
            float m_screen_width = 800;
            void update_view_matrix();
            void update_projection_matrix();

            glm::vec3 m_direction;
            glm::vec3 m_right;
            glm::vec3 m_up;
            float m_clipping_plane = 100.f;
            float m_screen_aspect;

            static constexpr glm::vec3 s_world_up{ 0, 0, 1 };
            static constexpr glm::vec3 s_world_right{ 0, -1, 0 };
            static constexpr glm::vec3 s_world_forward{ 1, 0, 0 };
            glm::mat4 m_view_matrix;
            glm::mat4 m_projection_matrix;
            
            bool m_update_view_matrix = false;

            Transform *m_transform;
    };
    REGISTER_COMPONENT(Camera);
}
