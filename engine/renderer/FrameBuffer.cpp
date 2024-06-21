
#include "FrameBuffer.hpp"

#include <glad/glad.h>
#include <Log.hpp>
namespace H4_engine
{

    FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
    {
        glGenFramebuffers(1, &m_id);
    }
    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &m_id);
    }

    void FrameBuffer::check()
    {
        bind();
        auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
            LOG_ERROR("FRAMEBUFFER:: Framebuffer is not complete! {0}", fboStatus);
    }

    void FrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }

    void FrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::bind_texture(Texture *texture, GLenum attachment)
    {
        bind();
        glFramebufferTexture(GL_DRAW_FRAMEBUFFER, attachment, texture->get_id(), 0);
    }
}