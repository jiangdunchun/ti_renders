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
    mat4 PV;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    vec4 model_pos = uModel * vec4(aPosition, 1.0f);

    vs_out.PV = uProjection * uView;

    vs_out.frag_position = model_pos.rgb;

    vs_out.tex_coord = aTex_coord;

    vs_out.normal = (uModel * vec4(aNormal, 1.0f)).rgb;

    mat3 model_mat = mat3(transpose(inverse(uModel)));
    vec3 T = normalize(model_mat * aTangent);
    vec3 N = normalize(model_mat * aNormal);
    vec3 B = normalize(cross(N,T));
    vs_out.TBN = transpose(mat3(T, B, N));

    gl_Position = vs_out.PV * model_pos;
}

#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT {
    vec3 frag_position;
    vec2 tex_coord;
    vec3 normal;
    mat3 TBN;
    mat4 PV;
} fs_in;

uniform vec3 uView_position;
uniform vec2 uScreen;
uniform sampler2D uPosition;
uniform sampler2D uBase_color;
uniform samplerCube uEnvironment;

layout(location = 0) out vec4 fColor;


void main() {
    vec3 V = normalize(uView_position - fs_in.frag_position);
    vec3 R = reflect(-1.0f * V, fs_in.normal);

    vec4 p_position = fs_in.PV * vec4(fs_in.frag_position, 1.0f);
    vec2 uv = p_position.xy / p_position.w;

    fColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
