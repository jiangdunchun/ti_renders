#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;

out VS_OUT{
    vec4 position;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    vs_out.position = uModel * vec4(aPosition, 1.0f);
    gl_Position = uProjection * uView * vs_out.position;
}


#__GEOMTRY_SHADER__

#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT{
    vec4 position;
} fs_in;

uniform vec3 uLight_position;
uniform float uLight_radius;

layout(location = 0) out vec3 fDepth;

void main() {
    float depth = length((1.0f / fs_in.position.w) * fs_in.position.xyz - uLight_position);
    if (depth > uLight_radius) depth = uLight_radius;
    fDepth = vec3(depth);
}
