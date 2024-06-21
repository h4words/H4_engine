#version 460
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 texture_coord;
layout(location = 2) in vec3 normal_coord;

uniform mat4 model_matrix;
uniform mat4 view_projection_matrix;

out vec3 Normal;
out vec2 tex_coord;
out vec3 frag_pos;
void main() {
    frag_pos = vec3(model_matrix * vec4(vertex_position, 1.0));
    Normal = transpose(inverse(mat3(model_matrix))) * normal_coord;
    tex_coord = texture_coord;
    gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
}