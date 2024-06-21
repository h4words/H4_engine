#pragma once

#include "VertexBuffer.hpp"

namespace H4_engine {
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void add_buffer(const VertexBuffer& vertex_buffer);
        void bind() const;
        void unbind();

    private:
        unsigned int m_id = 0;
        unsigned int m_elements_count = 0;
    };

}