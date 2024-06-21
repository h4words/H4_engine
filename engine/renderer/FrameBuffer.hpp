#pragma once

#include <glad/glad.h>
#include <renderer/Cubemap.hpp>
#include <renderer/Texture.hpp>

namespace H4_engine
{
    class FrameBuffer
    {
        public:
            FrameBuffer(unsigned int width, unsigned int height);
            ~FrameBuffer();
            void check();
            void bind();
            void unbind();
            void bind_texture(Texture *texture, GLenum attachment);
            unsigned int get_texture_id() { return texture_id; }
        private:
            unsigned int m_id = 0;
            unsigned int renderbuffer_id = 0;
            unsigned int texture_id = 0;
    };
}