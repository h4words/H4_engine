#include "Texture2D.hpp"

namespace H4_engine
{
    Texture2D *Texture2D::blank = nullptr;
    Texture2D::Texture2D(const unsigned char* data, unsigned int width, unsigned int height, GLenum comp)
        : m_width(width)
        , m_height(height)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (data)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, comp, width, height, 0, comp, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_id);
    }
    void Texture2D::bind(unsigned int unit)
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
    void Texture2D::unbind(unsigned int unit)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}