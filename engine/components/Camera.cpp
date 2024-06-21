#include "Camera.hpp"
#include "Log.hpp"
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace H4_engine {
    Camera::Camera(Entity *entity)
        : Component(entity) { }
    
    void Camera::start()
    {
        m_transform = m_entity->get_component<Transform>();
        m_transform->add_position_callback([&](glm::vec3 old, glm::vec3 now)
        {
            m_update_view_matrix = true;
        });
        m_transform->add_rotation_callback([&](glm::vec3 old, glm::vec3 now)
        {
            m_update_view_matrix = true;
        });
        update_view_matrix();
        update_projection_matrix();
    }

    glm::mat4 Camera::get_view_matrix()
    {
        if (m_update_view_matrix)
        {
            update_view_matrix();
        }
        return m_view_matrix;
    }
    glm::mat4 Camera::get_projection_matrix()
    {
        if(m_update_projection_matrix)
        {
            update_projection_matrix();
            m_update_projection_matrix = false;
        }
        return m_projection_matrix;
    }
    void Camera::update_view_matrix()
    {
        glm::vec3 m_position = m_transform->get_position();
        glm::vec3 m_rotation = m_transform->get_rotation();
        const float roll_in_radians  = glm::radians(m_rotation.x);
        const float pitch_in_radians = glm::radians(m_rotation.x);
        const float yaw_in_radians   = glm::radians(m_rotation.y);
        
        glm::vec3 front;
        front.x = cos(yaw_in_radians) * cos(pitch_in_radians);
        front.y = sin(pitch_in_radians);
        front.z = sin(yaw_in_radians) * cos(pitch_in_radians);
        m_direction = glm::normalize(front);
        m_right = glm::normalize(glm::cross(m_direction, {0, 1, 0}));
        m_up = glm::normalize(glm::cross(m_right, m_direction));

        m_view_matrix = glm::lookAt(m_position, m_position + m_direction, m_up);
    }
    
    void Camera::update_projection_matrix()
    {
        m_projection_matrix = glm::perspective(glm::radians(60.0f), m_screen_width / m_screen_height, 0.01f, m_clipping_plane);
    }

    void Camera::move_forward( float delta)
    {
        glm::vec3 m_position = m_transform->get_position();
        m_position += m_direction * delta;
        m_update_view_matrix = true;
    }
    void Camera::set_aspect( float screen_aspect )
    { 
        m_screen_aspect = screen_aspect;
        m_update_projection_matrix = true;
    }
    void Camera::move_right( float delta)
    {
        glm::vec3 m_position = m_transform->get_position();
        m_position += m_right * delta;
        m_update_view_matrix = true;
    }

    void Camera::move_up( float delta)
    {
        glm::vec3 m_position = m_transform->get_position();
        m_position += m_up * delta;
        m_update_view_matrix = true;
    }
    void Camera::set_clipping_plane( float amount)
    {
        m_clipping_plane = amount;
    }

    void Camera::add_movement_and_rotation( glm::vec3 movement_delta,
                                            glm::vec3 rotation_delta)
    {
        glm::vec3 m_position = m_transform->get_position();
        glm::vec3 m_rotation = m_transform->get_rotation();
        if (movement_delta == vec3_zero && rotation_delta == vec3_zero) return;
        m_position += m_right            * movement_delta.x;
        m_position += m_up               * movement_delta.y;
        m_position += m_direction        * movement_delta.z;
        m_rotation += rotation_delta;
        if (m_rotation.x > 89) m_rotation.x = 89;
        if (m_rotation.x < -89) m_rotation.x = -89;
        m_transform->set_position(m_position);
        m_transform->set_rotation(m_rotation);
    }
}
