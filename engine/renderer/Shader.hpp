#pragma once

#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>
#include <string>
namespace H4_engine {
    class Shader
    {
    public:
        Shader(std::string name);
        ~Shader();
        void bind();
        void unbind();

        bool is_compiled() { return m_is_compiled; }
        void set_matrix4(const char* name, glm::mat4 matrix);
        void set_matrix3(const char* name, glm::mat3 matrix);
        void set_int(const char* name, int value);
        void set_float(const char* name, float value);
        void set_vec3(const char* name, glm::vec3 value);

    private:
        unsigned int m_id = 0;
        bool m_is_compiled = false;
    };
}