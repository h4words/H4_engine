#version 460
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 color;
    
    int depthMap_layer;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 color;
    
    int depthMap_layer;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 color;

    int depthMap_layer;
};

#define LIGHTS_MAX 16

uniform int nr_dir_lights;
uniform int nr_point_lights;
uniform int nr_spot_lights;
uniform DirLight dirLights[LIGHTS_MAX];
uniform PointLight pointLights[LIGHTS_MAX];
uniform SpotLight spotLights[LIGHTS_MAX];

in vec3 frag_pos;
in vec3 Normal;
in vec2 tex_coord;

out vec4 frag_color;

uniform vec3 viewPos;

//uniform Material material;
layout(binding = 0) uniform sampler2D diffuse_tex;
layout(binding = 1) uniform samplerCubeArray depthCubemaps;
layout(binding = 2) uniform sampler2DArray depthMaps;
uniform float far_plane;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - frag_pos);

    vec3 result = vec3(0);

    for(int i = 0; i < nr_dir_lights; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);

    for(int i = 0; i < nr_point_lights; i++)
        result += CalcPointLight(pointLights[i], norm, viewDir);

    for(int i = 0; i < nr_spot_lights; i++)
        result += CalcSpotLight(spotLights[i], norm, viewDir);

    frag_color = vec4(result, texture(diffuse_tex, tex_coord).w);
}

float ShadowCalculation(vec3 lightPos, int layer)
{
    vec3 fragToLight = frag_pos - lightPos;
    float closestDepth = texture(depthCubemaps, vec4(fragToLight, layer)).r;
    closestDepth *= far_plane;
    float currentDepth = length(fragToLight);
    float bias = 0.05; 
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}  

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);

    vec3 ambient = vec3(texture(diffuse_tex, tex_coord));
    vec3 diffuse = light.color * diff * vec3(texture(diffuse_tex, tex_coord));
    //diffuse *= (1.0 - ShadowCalculation(light.position));
    return (ambient + diffuse);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - frag_pos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);

    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient = vec3(texture(diffuse_tex, tex_coord));
    vec3 diffuse = light.color * attenuation * diff * vec3(texture(diffuse_tex, tex_coord));
    ambient *= 0.05;
    diffuse *= (1.0 - ShadowCalculation(light.position, light.depthMap_layer));
    return (ambient + diffuse);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - frag_pos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);

    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = vec3(texture(diffuse_tex, tex_coord));
    vec3 diffuse = light.color * diff * vec3(texture(diffuse_tex, tex_coord));
    ambient *= 0.05;
    diffuse *= attenuation * intensity;
    diffuse *= (1.0 - ShadowCalculation(light.position, light.depthMap_layer));
    return (ambient + diffuse);
}