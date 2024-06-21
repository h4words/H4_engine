#pragma once

#include <glad/glad.h>
#include <renderer/Cubemap.hpp>
#include <renderer/Texture2D.hpp>
#include <renderer/FrameBuffer.hpp>

namespace H4_engine
{
    class FrameBuffer;
    class ArrayTexture : Texture
    {
        public:
            ArrayTexture(unsigned int resolution, unsigned int layers);
            ~ArrayTexture();
            void bind(unsigned int unit);
            void unbind(unsigned int unit);
            void bind_framebuffer();
            void unbind_framebuffer();
            unsigned int get_resolution() { return m_resolution; }
        private:
            FrameBuffer *m_framebuffer;
            unsigned int m_resolution;
    };

    class CubemapArrayTexture : Texture
    {
        public:
            CubemapArrayTexture(unsigned int resolution, unsigned int cubemaps);
            ~CubemapArrayTexture();
            void bind(unsigned int unit);
            void unbind(unsigned int unit);
            void bind_framebuffer();
            void unbind_framebuffer();
            unsigned int get_resolution() { return m_resolution; }
        private:
            FrameBuffer *m_framebuffer;
            unsigned int m_resolution;
    };
}