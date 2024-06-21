#version 460
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D text;
uniform vec3 textColor;
out vec4 frag_color;
void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    frag_color = vec4(textColor, 1.0) * sampled;
}