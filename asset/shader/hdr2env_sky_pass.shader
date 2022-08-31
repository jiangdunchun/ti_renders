#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;

out VS_OUT {
    vec3 position;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;

void main() {
    vs_out.position = aPosition;
    gl_Position = uProjection * uView * vec4(aPosition, 1.0f);
}


#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT {
    vec3 position;
} fs_in;

uniform sampler2D uHDR;

layout(location = 0) out vec3 fEnv;

const vec2 invAtan = vec2(0.1591, 0.3183);

vec2 SampleSphericalMap(vec3 v) {
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main() {
    vec2 uv = SampleSphericalMap(normalize(fs_in.position));
    fEnv = texture(uHDR, uv).rgb;
}
