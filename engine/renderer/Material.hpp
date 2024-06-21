#pragma once

#include <glm/glm.hpp>
#include <renderer/Texture2D.hpp>

namespace H4_engine
{
    class Material
    {
        public:
            Material(Texture2D* diffuseTex, glm::vec3 diffuseCol)
			    : diffuseTexture(diffuseTex) 
                , diffuseColor(diffuseCol) { }
            void bind() { diffuseTexture->bind(0); }
            void unbind() { diffuseTexture->unbind(0); }
            glm::vec3 get_diffuse_color() { return diffuseColor; }
            Texture2D* get_diffuse_texture() { return diffuseTexture; }
        private:
            Texture2D *diffuseTexture;
            glm::vec3 diffuseColor;
    };
}