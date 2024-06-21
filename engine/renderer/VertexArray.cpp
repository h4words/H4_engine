
#include "VertexArray.hpp"

#include <glad/glad.h>
#include <Log.hpp>
namespace H4_engine {

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_id);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    void VertexArray::bind() const
    {
        try {
            if (!m_id) return;
            glBindVertexArray(m_id);
        }
        catch (std::exception e){

        }
    }

    void VertexArray::unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::add_buffer(const VertexBuffer& vertex_buffer)
    {
        bind();
        vertex_buffer.bind();

        for (const BufferElement& current_element : vertex_buffer.get_layout().get_elements())
        {
            glEnableVertexAttribArray(m_elements_count);
            glVertexAttribPointer(
            	m_elements_count,
                static_cast<GLint>(current_element.components_count),
				current_element.component_type,
                GL_FALSE,
                static_cast<GLsizei>(vertex_buffer.get_layout().get_stride()),
                reinterpret_cast<const void*>(current_element.offset)
            );
            ++m_elements_count;
        }
    }
}