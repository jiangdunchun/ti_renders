#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;

out VS_OUT{
    vec3 tex_coord;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;

void main() {
    vs_out.tex_coord = normalize(aPosition);
    gl_Position = uProjection * uView * vec4(aPosition, 1.0f);
}


#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT{
    vec3 tex_coord;
} fs_in;

uniform sampler2D uEnvironment;

layout(location = 0) out vec3 fBackgroud;

const vec2 INV_ATAN = vec2(0.1591, 0.3183);

vec2 sample_spherical_map(vec3 v) {
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= INV_ATAN;
    uv += 0.5;
    return uv;
}

void main() {
    vec2 uv = sample_spherical_map(normalize(fs_in.tex_coord));
    fBackgroud = texture(uEnvironment, uv).rgb;
}