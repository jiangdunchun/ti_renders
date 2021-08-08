#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTex_coord;

out VS_OUT {
    vec2 tex_coord;
} vs_out;

void main() {
    vs_out.tex_coord = aTex_coord;

    gl_Position = vec4(aPosition, 1.0f);
}

#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT {
    vec2 tex_coord;
} fs_in;

uniform sampler2D uPosition;
uniform sampler2D uBase_color;
uniform sampler2D uNormal;
uniform sampler2D uMaterial;

uniform vec3 uView_position;

struct Point_Light {
    vec3 position;
    vec3 intensity;
    samplerCube shadow_map;
    float bias;
    float radius;
};
const int LIGHTS_MAX = 1;
uniform int uSpot_lights_num;
uniform Point_Light uSpot_lights[LIGHTS_MAX];

uniform samplerCube uDiffuse;
uniform samplerCube uSpecular;
uniform sampler2D uLUT;

layout(location = 0) out vec4 fColor;

const float PI = 3.14159265359f;

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0f);
    float NdotH2 = NdotH * NdotH;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0f) + 1.0f);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0f);
    float k = (r * r) / 8.0f;

    float nom = NdotV;
    float denom = NdotV * (1.0f - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0f);
    float NdotL = max(dot(N, L), 0.0f);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0f - F0) * pow(1.0f - cosTheta, 5.0f);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) {
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

void main() {
    vec3 base_color = texture(uBase_color, fs_in.tex_coord).rgb;
    vec3 position = texture(uPosition, fs_in.tex_coord).rgb;
    vec3 normal = texture(uNormal, fs_in.tex_coord).rgb;
    float metallic = texture(uMaterial, fs_in.tex_coord).r;
    float roughness = texture(uMaterial, fs_in.tex_coord).g;
    float ao = texture(uMaterial, fs_in.tex_coord).b;
    
    vec3 view_dir = normalize(uView_position - position);

    vec3 F0 = vec3(0.04f);
    F0 = mix(F0, base_color, metallic);

    vec3 light = vec3(0.0f);
    for (int i = 0; i < uSpot_lights_num; i++) {
        vec3 light_dir = normalize(uSpot_lights[i].position - position);
        float light_dis = length(uSpot_lights[i].position - position);
        
        if (texture(uSpot_lights[i].shadow_map, -1.0f * light_dir).r + uSpot_lights[i].bias > light_dis) {
            vec3 light_color = uSpot_lights[i].intensity;
            vec3 half_dir = normalize(view_dir + light_dir);
            float light_radiens = (uSpot_lights[i].radius - light_dis) / uSpot_lights[i].radius;

            float NDF = DistributionGGX(normal, half_dir, roughness);
            float G = GeometrySmith(normal, view_dir, light_dir, roughness);
            vec3 F = fresnelSchlick(max(dot(half_dir, view_dir), 0.0f), F0);

            vec3 kS = F;
            vec3 kD = vec3(1.0f) - kS;
            kD *= 1.0f - metallic;

            vec3 nominator = NDF * G * F;
            float denominator = 4.0f * max(dot(normal, view_dir), 0.0f) * max(dot(normal, light_dir), 0.0f) + 0.001f;
            vec3 specular = nominator / denominator;

            float NdotL = max(dot(normal, light_dir), 0.0f);
            light += (kD * base_color / PI + specular) * light_color * NdotL * light_radiens;
        }
    }

    //vec3 view_dir = normalize(uView_position - position);

    //vec3 F0 = vec3(0.04f);
    //F0 = mix(F0, base_color, metallic);

    //vec3 light_dir = normalize(vec3(1.0f, 0.0f, 1.0f));
    //vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    //vec3 half_dir = normalize(view_dir + light_dir);

    //float NDF = DistributionGGX(normal, half_dir, roughness);
    //float G = GeometrySmith(normal, view_dir, light_dir, roughness);
    //vec3 F = fresnelSchlick(max(dot(half_dir, view_dir), 0.0f), F0);

    //vec3 kS = F;
    //vec3 kD = vec3(1.0f) - kS;
    //kD *= 1.0f - metallic;

    //vec3 nominator = NDF * G * F;
    //float denominator = 4.0f * max(dot(normal, view_dir), 0.0f) * max(dot(normal, light_dir), 0.0f) + 0.001f;
    //vec3 specular = nominator / denominator;

    //float NdotL = max(dot(normal, light_dir), 0.0f);
    //vec3 light = (kD * base_color / PI + specular) * light_color * NdotL;

    // vec3 kS_environment = fresnelSchlick(max(dot(normal, view_dir), 0.0f), F0);
    // vec3 kD_environment = 1.0f - kS_environment;
    // vec3 ambient = (kD_environment * texture(uDiffuse, normal).rgb * base_color) * ao;
    //vec3 ambient = vec3(0.01) * base_color * ao;
    vec3 R = reflect(-1.0 * view_dir, normal);
    vec3 F = fresnelSchlickRoughness(max(dot(normal, view_dir), 0.0), F0, roughness);

    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;     

    vec3 irradiance = texture(uDiffuse, normal).rgb;
    vec3 diffuse    = irradiance * base_color;

    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(uSpecular, R,  roughness * MAX_REFLECTION_LOD).rgb;   
    vec2 envBRDF  = texture(uLUT, vec2(max(dot(normal, view_dir), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (F * envBRDF.x + envBRDF.y);

    vec3 ambient = (kD * diffuse + specular) * ao;

    vec3 color = ambient + light;

    color = color / (color + vec3(1.0f));
    color = pow(color, vec3(1.0f / 2.2f));

    fColor = vec4(color, 1.0f);
}
