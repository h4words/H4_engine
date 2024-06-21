
#include "Shader.hpp"
#include "Log.hpp"
#include <sys/stat.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

namespace H4_engine
{
    bool create_shader(const char* source, GLenum shader_type, GLuint& shader_id)
    {
        shader_id = glCreateShader(shader_type);
        glShaderSource(shader_id, 1, &source, nullptr);
        glCompileShader(shader_id);

        GLint success;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            char info_log[1024];
            glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);

            LOG_ERROR("Shader compilation error:\n {0}", info_log);
            return false;
        }
        return true;
    }

    std::string ReadTextFromFile(std::string path) {
        std::ifstream file(path);
        std::string str;
        std::string line;
        while (std::getline(file, line)) {
            str += line + "\n";
        }
        return str;
    }

    bool exists(const std::string& name) {
        struct stat buffer;   
        return (stat (name.c_str(), &buffer) == 0); 
    }

    Shader::Shader(std::string name)
    {
        GLuint vertex_shader_id = 0;
        if (!create_shader(ReadTextFromFile("resources/shaders/" + name + ".vert").c_str(), GL_VERTEX_SHADER, vertex_shader_id))
        {
        	LOG_ERROR("VERTEX SHADER: compile-time error!");
            glDeleteShader(vertex_shader_id);
            return;
        }
        GLuint fragment_shader_id = 0;
        if (!create_shader(ReadTextFromFile("resources/shaders/" + name + ".frag").c_str(), GL_FRAGMENT_SHADER, fragment_shader_id))
        {
        	LOG_ERROR("FRAGMENT SHADER: compile-time error!");
            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);
            return;
        }
        GLuint geometry_shader_id = 0;
        bool geometry = false;
        if (exists("resources/shaders/" + name + ".geom"))
        {
            if (!create_shader(ReadTextFromFile("resources/shaders/" + name + ".geom").c_str(), GL_GEOMETRY_SHADER, geometry_shader_id))
            {
                LOG_ERROR("GEOMETRY SHADER: compile-time error!");
                glDeleteShader(vertex_shader_id);
                glDeleteShader(fragment_shader_id);
                glDeleteShader(geometry_shader_id);
                return;
            }
            geometry = true;
        }
        else
        {
            LOG_WARN(name + " shader has no geometry shader.");
        }
        m_id = glCreateProgram();
        glAttachShader(m_id, vertex_shader_id);
        glAttachShader(m_id, fragment_shader_id);
        if (geometry)
            glAttachShader(m_id, geometry_shader_id);
        glLinkProgram(m_id);

        GLint success;
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            GLchar info_log[1024];
            glGetProgramInfoLog(m_id, 1024, nullptr, info_log);
            LOG_ERROR("SHADER PROGRAM: Link-time error:\n{0}", info_log);
            glDeleteProgram(m_id);
            m_id = 0;
            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);
            if (geometry)
                glDeleteShader(geometry_shader_id);
            return;
        }
        else
        {
            m_is_compiled = true;
        }

        glDetachShader(m_id, vertex_shader_id);
        glDetachShader(m_id, fragment_shader_id);
        glDetachShader(m_id, geometry_shader_id);
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
        glDeleteShader(geometry_shader_id);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_id);
    }

    void Shader::bind()
    {
        glUseProgram(m_id);
    }

    void Shader::unbind()
    {
        glUseProgram(0);
    }

    void Shader::set_matrix4(const char* name, glm::mat4 matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::set_matrix3(const char* name, glm::mat3 matrix)
    {
        glUniformMatrix3fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::set_int(const char* name, int value)
    {
        glUniform1i(glGetUniformLocation(m_id, name), value);
    }

    void Shader::set_float(const char* name, float value)
    {
        glUniform1f(glGetUniformLocation(m_id, name), value);
    }

    void Shader::set_vec3(const char* name, glm::vec3 value)
    {
        glUniform3f(glGetUniformLocation(m_id, name), value.x, value.y, value.z);
    }
}