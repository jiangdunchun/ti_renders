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

uniform vec3 uView;

uniform samplerCube uDiffuse;
uniform samplerCube uSpecular;
uniform sampler2D uLUT;

const int LIGHTS_MAX = 1;

struct POINT_LIGHT {
    vec3 position;
    vec3 intensity;
    samplerCube shadow_map;
    float bias;
    float radius;
};
uniform int uPoint_lights_num;
uniform POINT_LIGHT uPoint_lights[LIGHTS_MAX];

layout(location = 0) out vec4 fColor;

const float PI = 3.14159265359f;

const float MAX_REFLECTION_LOD = 4.0;

const float LIGHT_MODEL_SINGLE_COLOR = 1.0f;
const float LIGHT_MODEL_PBR = 2.0f;

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
    float light_model = texture(uMaterial, fs_in.tex_coord).a;
    float alpha = texture(uBase_color, fs_in.tex_coord).a;
    vec3 base_color = texture(uBase_color, fs_in.tex_coord).rgb;
    vec3 position = texture(uPosition, fs_in.tex_coord).rgb;
    vec3 N = texture(uNormal, fs_in.tex_coord).rgb;
    float metallic = texture(uMaterial, fs_in.tex_coord).r;
    float roughness = texture(uMaterial, fs_in.tex_coord).g;
    float ao = texture(uMaterial, fs_in.tex_coord).b;


    // light model pbr
    if (light_model - LIGHT_MODEL_PBR < 0.001f) {
        vec3 V = normalize(uView - position);

        vec3 F0 = vec3(0.04f);
        F0 = mix(F0, base_color, metallic);

        vec3 light = vec3(0.0f);
        for (int i = 0; i < uPoint_lights_num; i++) {
            vec3 L = normalize(uPoint_lights[i].position - position);
            float distance = length(uPoint_lights[i].position - position);
            
            if (texture(uPoint_lights[i].shadow_map, -1.0f * L).r + uPoint_lights[i].bias > distance) {
                vec3 intensity = uPoint_lights[i].intensity;
                vec3 H = normalize(V + L);
                float radiens = (uPoint_lights[i].radius - distance) / uPoint_lights[i].radius;

                float NDF = DistributionGGX(N, H, roughness);
                float G = GeometrySmith(N, V, L, roughness);
                vec3 F = fresnelSchlick(max(dot(H, V), 0.0f), F0);

                vec3 kS = F;
                vec3 kD = vec3(1.0f) - kS;
                kD *= 1.0f - metallic;

                vec3 nominator = NDF * G * F;
                float denominator = 4.0f * max(dot(N, V), 0.0f) * max(dot(N, L), 0.0f) + 0.001f;
                vec3 specular = nominator / denominator;

                float NdotL = max(dot(N, L), 0.0f);
                light += (kD * base_color / PI + specular) * intensity * NdotL * radiens;
            }
        }
        
        vec3 R = reflect(-1.0 * V, N);
        vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);

        vec3 kS = F;
        vec3 kD = 1.0 - kS;
        kD *= 1.0 - metallic;

        vec3 irradiance = texture(uDiffuse, N).rgb;
        vec3 diffuse = irradiance * base_color;

        vec3 prefiltered_color = textureLod(uSpecular, R,  roughness * MAX_REFLECTION_LOD).rgb;   
        vec2 envBRDF  = texture(uLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
        vec3 specular = prefiltered_color * (F * envBRDF.x + envBRDF.y);

        vec3 ambient = (kD * diffuse + specular) * ao;

        fColor = vec4(light + ambient, alpha);
    }
}
