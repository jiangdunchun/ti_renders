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

uniform samplerCube uSky;

layout(location = 0) out vec3 fColor;

void main() {
    fColor = texture(uSky, fs_in.tex_coord).rgb;
}
