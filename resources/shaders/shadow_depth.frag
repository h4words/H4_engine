#version 460
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;
out vec4 frag_color;

void main()
{
    // вычисление расстояния между фрагментом и источником 
    float lightDistance = length(FragPos.xyz - lightPos);
    
    // преобразование к интервалу [0, 1] посредством деления на far_plane
    lightDistance = lightDistance / far_plane;
    
    // запись результата в результирующую глубину фрагмента
    gl_FragDepth = lightDistance;
    //frag_color = vec4(vec3(1), 1);
}  