#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTex_coord;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBi_tangent;

out VS_OUT {
    vec3 frag_position;
    vec2 tex_coord;
    vec3 normal;
    mat3 TBN;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    vec4 model_pos = uModel * vec4(aPosition, 1.0f);
    vec4 projection_pos = uProjection * uView * model_pos;

    vs_out.frag_position = model_pos.rgb;

    vs_out.tex_coord = aTex_coord;

    vs_out.normal = aNormal;

    mat3 model_mat = mat3(transpose(inverse(uModel)));
    vec3 T = normalize(model_mat * aTangent);
    vec3 N = normalize(model_mat * aNormal);
    vec3 B = normalize(model_mat * aBi_tangent);
    vs_out.TBN = transpose(mat3(T, B, N));

    gl_Position = projection_pos;
}

#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT {
    vec3 frag_position;
    vec2 tex_coord;
    vec3 normal;
    mat3 TBN;
} fs_in;

uniform int uLight_model;

uniform vec3 uView_position;

uniform vec3 uBase_color_val;
uniform sampler2D uBase_color_map;
uniform sampler2D uNormal_map;
uniform float uMetallic_val;
uniform sampler2D uMetallic_map;
uniform float uRoughness_val;
uniform sampler2D uRoughness_map;
uniform sampler2D uHeight_map;
uniform float uHeight_val;
uniform sampler2D uAo_map;
uniform sampler2D uEmissive_map;

layout(location = 0) out vec3 fPosition;
layout(location = 1) out vec4 fBase_color;
layout(location = 2) out vec3 fNormal;
layout(location = 3) out vec4 fMaterial;
layout(location = 4) out vec3 fEmissive;

bool is_sample2d_null(sampler2D texture) {
    int flag = textureSize(texture, 0).r + textureSize(texture, 0).g;
    if (flag > 2) return false;
    else return true;
}

vec2 parallax_mapping(vec2 tex_coord, vec3 V) {
    if (is_sample2d_null(uHeight_map)) return tex_coord;

    float height = texture(uHeight_map, tex_coord).r;
    vec2 p = V.rg * (height * 1.0f);
    return tex_coord + p;
}

void main() {
    vec2 tex_coord = parallax_mapping(fs_in.tex_coord, fs_in.TBN * normalize(uView_position - fs_in.frag_position));
    if (tex_coord.x > 1.0 || tex_coord.y > 1.0 || tex_coord.x < 0.0 || tex_coord.y < 0.0) discard;

    fPosition = fs_in.frag_position;

    if (is_sample2d_null(uBase_color_map)) fBase_color = vec4(uBase_color_val, 1.0f);
    else fBase_color = vec4(pow(texture(uBase_color_map, fs_in.tex_coord).rgb, vec3(2.2f)), 1.0f);

    if (is_sample2d_null(uNormal_map)) fNormal = fs_in.normal;
    else fNormal = normalize(inverse(fs_in.TBN) * (texture(uNormal_map, fs_in.tex_coord).rgb * 2.0f - 1.0f));

    if (is_sample2d_null(uMetallic_map)) fMaterial.r = uMetallic_val;
    else fMaterial.r = texture(uMetallic_map, fs_in.tex_coord).r;

    if (is_sample2d_null(uRoughness_map)) fMaterial.g = uRoughness_val;
    else fMaterial.g = texture(uRoughness_map, fs_in.tex_coord).r;

    if (is_sample2d_null(uAo_map)) fMaterial.b = 1.0f;
    else fMaterial.b = texture(uAo_map, fs_in.tex_coord).r;

    fMaterial.a = float(uLight_model);

    if (is_sample2d_null(uEmissive_map)) fEmissive = vec3(0.0f, 0.0f, 0.0f);
    else fEmissive = pow(texture(uEmissive_map, fs_in.tex_coord).rgb, vec3(2.2f));
}
