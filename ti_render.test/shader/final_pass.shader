#__VERTEX_SHADER__
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTex_coord;

out VS_OUT
{
    vec2 tex_coord;
} vs_out;

void main() 
{
    vs_out.tex_coord = aTex_coord;
    gl_Position = vec4(aPosition, 1.0f);
}

#__GEOMTRY_SHADER__


#__FRAGMENT_SHADER__
#version 330 core
in VS_OUT
{
    vec2 tex_coord;
} fs_in;

uniform sampler2D uColor;
uniform sampler2D uSky;
uniform sampler2D uEmissive;
uniform sampler2D uID;

out vec4 fColor;

void main() {
    vec4 id = texture(uID, fs_in.tex_coord);
    float sum = id.r + id.g + id.b + id.a;
    fColor = vec4(sum > 0.001f?texture(uColor, fs_in.tex_coord).rgb:texture(uSky, fs_in.tex_coord).rgb, 1.0f);
    fColor += vec4(texture(uEmissive, fs_in.tex_coord).rgb, 1.0f);
}
