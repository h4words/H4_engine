
#include "ArrayTexture.hpp"

#include <glad/glad.h>
#include <Log.hpp>
namespace H4_engine
{
    ArrayTexture::ArrayTexture(unsigned int resolution, unsigned int layers)
        : m_resolution(resolution)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexImage3D(
            GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, resolution, resolution, layers, 0,
            GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

        m_framebuffer = new FrameBuffer(resolution, resolution);
        m_framebuffer->bind();

        m_framebuffer->bind_texture(this, GL_DEPTH_ATTACHMENT);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        m_framebuffer->check();

        m_framebuffer->unbind();
    }
    ArrayTexture::~ArrayTexture()
    {
        glDeleteFramebuffers(1, &m_id);
    }
    void ArrayTexture::bind(unsigned int unit) 
    { 
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
    };
    void ArrayTexture::unbind(unsigned int unit) 
    { 
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    };
    void ArrayTexture::bind_framebuffer() 
    { 
        m_framebuffer->bind(); 
    };
    void ArrayTexture::unbind_framebuffer() 
    { 
        m_framebuffer->unbind(); 
    };

    CubemapArrayTexture::CubemapArrayTexture(unsigned int resolution, unsigned int cubemaps)
        : m_resolution(resolution)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, m_id);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexImage3D(
            GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_DEPTH_COMPONENT, resolution, resolution, 6 * cubemaps, 0,
            GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);

        m_framebuffer = new FrameBuffer(resolution, resolution);
        m_framebuffer->bind();

        m_framebuffer->bind_texture(this, GL_DEPTH_ATTACHMENT);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        m_framebuffer->check();

        m_framebuffer->unbind();
    }
    CubemapArrayTexture::~CubemapArrayTexture()
    {
        glDeleteFramebuffers(1, &m_id);
    }
    void CubemapArrayTexture::bind(unsigned int unit) 
    { 
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, m_id);
    };
    void CubemapArrayTexture::unbind(unsigned int unit) 
    { 
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, m_id);
    };

    void CubemapArrayTexture::bind_framebuffer() 
    { 
        m_framebuffer->bind(); 
    };
    void CubemapArrayTexture::unbind_framebuffer() 
    { 
        m_framebuffer->unbind(); 
    };
}