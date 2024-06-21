#version 460
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex_cord;

uniform mat4 view_projection_matrix;
out vec2 TexCoords;

void main()
{
    TexCoords = tex_cord;
    gl_Position = view_projection_matrix * vec4(pos, 1.0, 1.0);
}