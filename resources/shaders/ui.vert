#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 texture_coord;

uniform mat4 view_projection_matrix;

out vec2 tex_coord;

void main() {
    tex_coord = texture_coord;
    gl_Position = view_projection_matrix * vec4(vertex_position.x, vertex_position.y, 0, 1.0);
}